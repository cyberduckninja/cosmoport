#include "log.hpp"


namespace components {


    void process_manager::run(dag_t &dag) {
        auto ctx = std::make_unique<dag_context_t>();
        for(auto&i:dag.job_list){
            ctx->push(i);
        }
        dag_contexts_.emplace(dag.name_,std::move(ctx));
    }
} // namespace cosmoport
