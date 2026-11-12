#include "tiny_experiment.hpp"

#include "helper.hpp"

using namespace tiny;

tiny_experiment::tiny_experiment(experiment_context* context)
{
    m_context = context;
}

std::vector<experiment_entry>& get_experiments()
{
    static std::vector<experiment_entry> instances;
    return instances;
}

int register_experiment(const std::string& category, const std::string& name, const experiment_type type,
                        experiment_create_function* function)
{
    auto& experiments = get_experiments();

    experiments.push_back({category, name, type, function});
    return static_cast<int>(experiments.size() - 1);
}

void select_experiment(experiment_context* context, int selection)
{
    auto& experiments = get_experiments();
    if (selection < 0 || selection >= static_cast<int>(experiments.size())) return;

    delete context->experiment;
    context->experiment = nullptr;

    context->type = experiments[selection].type;

    context->experiment_index = selection;
    context->experiment = experiments[selection].create_function(context);
}

int get_experiment_index(const std::string& name)
{
    auto& experiments = get_experiments();
    auto it = std::ranges::find(experiments, name, &experiment_entry::name);
    if (it != experiments.end())
    {
        return static_cast<int>(std::distance(experiments.begin(), it));
    }
    return -1;
}
