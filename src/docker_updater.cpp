#include "docker_updater.hpp"

#include <string.h>
#include <sys/wait.h>

#include "spdlog/fmt/fmt.h"
#include "spdlog/spdlog.h"

void DockerUpdater::update(std::string_view filepath)
{
    SPDLOG_INFO("[updater] Updating running docker container.");
    static constexpr std::string_view update_running_container_bash_format = R"literal(
image="$(docker load -i '{filepath}' | awk '/Loaded image:/{{print $NF}}' | cut -d':' -f1)"
container_name="$(echo $image | cut -d'/' -f2)"    
running_containers="$(docker ps -aq --filter "ancestor=$container_name")"
    
if [ -n "$(docker ps -q --filter "name=$container_name")" ]; then
    docker stop "$(docker ps -aq --filter "name=$container_name")" \
        && docker rm "$(docker ps -aq --filter "name=$container_name")";
fi;
docker run                                          \
    --device /dev/i2c-1                             \
    -v /sys:/sys                                    \
    --device /dev/gpiomem                           \
    --device /dev/gpiochip0                         \
    --device /dev/gpiochip1                         \
    -v /var/run/docker.sock:/var/run/docker.sock:ro \
    --network=host                                  \
    -t --init -d --restart unless-stopped           \
    --name $container_name $image
)literal";
    const auto ret_code = std::system(fmt::format(update_running_container_bash_format,
                                                  fmt::arg("filepath", filepath))
                                          .c_str());
    SPDLOG_INFO("[updater_app] Updating finished with status {}", WEXITSTATUS(ret_code));
}