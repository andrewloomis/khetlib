#ifndef GAMECONFIGS_H
#define GAMECONFIGS_H

#include <vector>
#include <memory>
#include <piece.h>
#include <pyramid.h>
#include <obelisk.h>
#include <pharoah.h>
#include <djed.h>

namespace Configs {
    std::vector<std::unique_ptr<Piece>> classic()
    {
        std::vector<std::unique_ptr<Piece>> config;
        config.push_back(std::make_unique<Pyramid>(7,0,270,Color::Red));
        config.push_back(std::make_unique<Pyramid>(2,1,0,Color::Red));
        config.push_back(std::make_unique<Pyramid>(0,3,180,Color::Red));
        config.push_back(std::make_unique<Pyramid>(0,4,270,Color::Red));
        config.push_back(std::make_unique<Pyramid>(6,5,270,Color::Red));
        config.push_back(std::make_unique<Pyramid>(7,3,270,Color::Red));
        config.push_back(std::make_unique<Pyramid>(7,4,180,Color::Red));
        config.push_back(std::make_unique<Obelisk>(6,0,0,Color::Red));
        config.push_back(std::make_unique<Obelisk>(4,0,0,Color::Red));
        config.push_back(std::make_unique<Pharoah>(5,0,0,Color::Red));

        config.push_back(std::make_unique<Pyramid>(3,2,90,Color::Grey));
        config.push_back(std::make_unique<Pyramid>(2,3,0,Color::Grey));
        config.push_back(std::make_unique<Pyramid>(2,4,90,Color::Grey));
        config.push_back(std::make_unique<Pyramid>(2,7,90,Color::Grey));
        config.push_back(std::make_unique<Pyramid>(9,3,90,Color::Grey));
        config.push_back(std::make_unique<Pyramid>(9,4,0,Color::Grey));
        config.push_back(std::make_unique<Pyramid>(7,6,180,Color::Grey));
        config.push_back(std::make_unique<Obelisk>(3,7,0,Color::Grey));
        config.push_back(std::make_unique<Obelisk>(5,7,0,Color::Grey));
        config.push_back(std::make_unique<Pharoah>(4,7,180,Color::Grey));

        config.push_back(std::make_unique<Djed>(4,3,0,Color::Red));
        config.push_back(std::make_unique<Djed>(5,3,90,Color::Red));
        config.push_back(std::make_unique<Djed>(4,4,90,Color::Grey));
        config.push_back(std::make_unique<Djed>(5,4,0,Color::Grey));
        return config;
    }

    std::vector<std::unique_ptr<Piece>> imhotep()
    {
        std::vector<std::unique_ptr<Piece>> config;
        config.push_back(std::make_unique<Pyramid>(0,3,180,Color::Red));
        config.push_back(std::make_unique<Pyramid>(0,4,270,Color::Red));
        config.push_back(std::make_unique<Pyramid>(6,2,180,Color::Red));
        config.push_back(std::make_unique<Pyramid>(6,5,270,Color::Red));
        config.push_back(std::make_unique<Pyramid>(5,4,90,Color::Red));
        config.push_back(std::make_unique<Pyramid>(8,3,270,Color::Red));
        config.push_back(std::make_unique<Pyramid>(8,4,180,Color::Red));
        config.push_back(std::make_unique<Obelisk>(6,0,0,Color::Red));
        config.push_back(std::make_unique<Obelisk>(4,0,0,Color::Red));
        config.push_back(std::make_unique<Pharoah>(5,0,0,Color::Red));

        config.push_back(std::make_unique<Pyramid>(1,3,0,Color::Grey));
        config.push_back(std::make_unique<Pyramid>(1,4,90,Color::Grey));
        config.push_back(std::make_unique<Pyramid>(3,2,90,Color::Grey));
        config.push_back(std::make_unique<Pyramid>(3,5,0,Color::Grey));
        config.push_back(std::make_unique<Pyramid>(4,3,270,Color::Grey));
        config.push_back(std::make_unique<Pyramid>(9,4,0,Color::Grey));
        config.push_back(std::make_unique<Pyramid>(9,3,90,Color::Grey));
        config.push_back(std::make_unique<Obelisk>(3,7,0,Color::Grey));
        config.push_back(std::make_unique<Obelisk>(5,7,0,Color::Grey));
        config.push_back(std::make_unique<Pharoah>(4,7,180,Color::Grey));

        config.push_back(std::make_unique<Djed>(7,0,90,Color::Red));
        config.push_back(std::make_unique<Djed>(5,3,90,Color::Red));
        config.push_back(std::make_unique<Djed>(4,4,90,Color::Grey));
        config.push_back(std::make_unique<Djed>(2,7,90,Color::Grey));
        return config;
    }


    std::vector<std::unique_ptr<Piece>> dynasty()
    {
        std::vector<std::unique_ptr<Piece>> config;
        config.push_back(std::make_unique<Pyramid>(0,2,180,Color::Red));
        config.push_back(std::make_unique<Pyramid>(0,3,270,Color::Red));
        config.push_back(std::make_unique<Pyramid>(4,0,0,Color::Red));
        config.push_back(std::make_unique<Pyramid>(6,0,270,Color::Red));
        config.push_back(std::make_unique<Pyramid>(4,2,0,Color::Red));
        config.push_back(std::make_unique<Pyramid>(3,4,90,Color::Red));
        config.push_back(std::make_unique<Pyramid>(5,4,270,Color::Red));
        config.push_back(std::make_unique<Obelisk>(5,0,0,Color::Red));
        config.push_back(std::make_unique<Obelisk>(5,2,0,Color::Red));
        config.push_back(std::make_unique<Pharoah>(5,1,0,Color::Red));

        config.push_back(std::make_unique<Pyramid>(3,7,90,Color::Grey));
        config.push_back(std::make_unique<Pyramid>(5,7,180,Color::Grey));
        config.push_back(std::make_unique<Pyramid>(5,5,180,Color::Grey));
        config.push_back(std::make_unique<Pyramid>(4,3,90,Color::Grey));
        config.push_back(std::make_unique<Pyramid>(6,3,270,Color::Grey));
        config.push_back(std::make_unique<Pyramid>(9,4,90,Color::Grey));
        config.push_back(std::make_unique<Pyramid>(9,5,0,Color::Grey));
        config.push_back(std::make_unique<Obelisk>(4,5,0,Color::Grey));
        config.push_back(std::make_unique<Obelisk>(4,7,0,Color::Grey));
        config.push_back(std::make_unique<Pharoah>(4,6,180,Color::Grey));

        config.push_back(std::make_unique<Djed>(2,3,0,Color::Red));
        config.push_back(std::make_unique<Djed>(6,2,90,Color::Red));
        config.push_back(std::make_unique<Djed>(3,5,90,Color::Grey));
        config.push_back(std::make_unique<Djed>(7,4,0,Color::Grey));
        return config;
    }
}

#endif // GAMECONFIGS_H
