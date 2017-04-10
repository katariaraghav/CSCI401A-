

#ifndef World_h
#define World_h

#include <vector>
#include "Singleton.h"


class World : public Singleton<World>
{
    friend class Singleton<World>;
public:

    
    std::vector<std::vector<std::vector<char>>>& GetIntersection() noexcept;

    int mMonth;
    bool intersectionLoaded = false;
private:

    std::vector<std::vector<std::vector<char>>> mIntersection;
};

#endif /* World_h */
