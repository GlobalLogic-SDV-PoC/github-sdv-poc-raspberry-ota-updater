#include <fstream>

#include "docker_updater.hpp"
#include "updater/app.hpp"

int main()
{
    static constexpr auto kConfigPath = "/var/config/main_config.json";
    auto docker_updater = std::make_shared<DockerUpdater>();

    updater::App app(docker_updater, nlohmann::json::parse(std::ifstream(kConfigPath)));
    app.initDefaultLogger("logs/logs.txt", 10'485'760, 3, std::chrono::seconds(5));
    app.init();
    app.start();
}