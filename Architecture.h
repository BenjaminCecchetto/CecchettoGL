/*
 * Architecture.h
 *
 *  Created on: Dec 13, 2013
 *      Author: root
 */

#ifndef CGL_ARCHITECTURE_H_
#define CGL_ARCHITECTURE_H_

#include <memory>
#include <vector>

#include "Program/Pass.h"

namespace cgl {

class Architecture;
typedef std::shared_ptr<Architecture> ArchitecturePtr;

class Architecture {
    std::vector<PassPtr> _passes;

public:
    Architecture() {
    }
    virtual ~Architecture() {
    }

    static ArchitecturePtr New() {
        return std::make_shared<Architecture>();
    }

    void AddPass(PassPtr pass) {
        _passes.push_back(pass);
    }

    virtual void Update(double dt) { (void)(dt); }

    void Loop(double dt) {
        Update(dt);

        for (PassPtr p : _passes)
        {
            p->Update(dt);
            p->Dispatch();
        }
    }
};


}

#endif /* ARCHITECTURE_H_ */
