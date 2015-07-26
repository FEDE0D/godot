
#ifndef STATE_H
#define STATE_H

#include "scene/main/node.h"
#include "scene/main/misc.h"

class State : public Node {

    OBJ_TYPE(State, Node);

protected:
    static void _bind_methods();

public:

    Node* get_context();

    State();

};

#endif // STATE_H
