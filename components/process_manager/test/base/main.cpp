#include <components/runner/process_manager.hpp>


int main() {
    components::process_manager pm;
    components::dag_t dag;
    dag.name_="test";
    components::job_t job;
    job.bin="/bin/bash";
    job.args =  { "-c", "for a in {1..10}; do sleep 2; echo 'Hello World ('$a')!'; done" };
    dag.job_list.emplace_back(job);
    pm.run(dag);
return 0;
}