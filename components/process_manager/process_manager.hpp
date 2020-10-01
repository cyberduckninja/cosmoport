#pragma once

#include <chrono>
#include <iostream>
#include <mutex>
#include <boost/asio.hpp>
#include <boost/process.hpp>
#include <string>
#include <queue>

namespace components {

    struct job_t final {
        boost::filesystem::path bin;
        std::vector<std::string> args;
        ///int parallel = 0;
    };

    struct dag_t final {
        std::string name_;
        std::list<job_t> job_list;
    };

    class job_context_t final {
    public:
        job_context_t(boost::asio::io_service &ios_)
                : in_(ios_), out_(ios_), error_(ios_) {}

        boost::process::async_pipe in_;
        boost::process::async_pipe out_;
        boost::process::async_pipe error_;
    };

    class dag_context_t {
    public:
        dag_context_t() : work_(boost::asio::make_work_guard(ios_)) {}

        ~dag_context_t() {
            ios_.stop();
            t_.join();
            std::error_code ec;
            group_.wait(ec);
            if (ec) {
                std::cerr << "Error" << std::endl;
            }
            for (auto &i:job_contexts_) {
                i.release();
            }
        }

        void push(job_t &j) {
            std::call_once(
                    flag_,
                    [this]() {
                        t_ = std::thread(
                                [this]() {
                                    ios_.run();
                                }
                        );
                    }
            );
            auto ctx = std::make_unique<job_context_t>(ios_);
            std::error_code ec;
            group_.add(
                    boost::process::child(
                            j.bin,
                            j.args,
                            group_,
                            boost::process::std_in < ctx->in_,
                            boost::process::std_out > ctx->out_,
                            boost::process::std_err > ctx->error_,
                            ios_
                    ),
                    ec);
            job_contexts_.emplace_back(std::move(ctx));
        }

    private:
        std::once_flag flag_;
        std::list<std::unique_ptr<job_context_t>> job_contexts_;
        boost::process::group group_;
        boost::asio::io_service ios_;
        boost::asio::executor_work_guard<boost::asio::io_service::executor_type> work_;
        std::thread t_;

    };


    class process_manager final {
    public:
        process_manager() = default;

        ~process_manager() = default;

        process_manager(const process_manager &) = delete;

        process_manager &operator=(const process_manager &) = delete;

        void run(dag_t &dag);

        void clear(const std::string &name) {
            dag_contexts_.at(name).release();
        }

    private:
        std::unordered_map<std::string, std::unique_ptr<dag_context_t>> dag_contexts_;

    };

} // namespace cosmoport
