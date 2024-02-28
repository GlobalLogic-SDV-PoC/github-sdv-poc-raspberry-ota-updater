#pragma once

#include "updater/interface/updater.hpp"

class DockerUpdater : public updater::IUpdater
{
public:
    void update(std::string_view filepath) override;
};