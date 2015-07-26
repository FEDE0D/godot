
#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include "scene/main/node.h"
#include "scene/main/misc.h"
#include "state.h"

class StateMachine : public Node {

    OBJ_TYPE(StateMachine, Node);

    ObjectID context_id;
    ObjectID current_state_id;

    bool enabled;
    NodePath context_node;
    NodePath current_state;

private:
    bool _can_process();
    State* _get_current_state();
    void _update_cache();

protected:
    void _notification(int p_what);
    static void _bind_methods();

public:
    void set_enabled(bool enable);
    bool is_enabled();

    void set_context_node(const NodePath& p_node);
    NodePath get_context_node();

    void set_current_state(const NodePath& p_node);
    NodePath get_current_state();

    void change_state(const NodePath& new_state);
    void update_machine(float delta);

    StateMachine();
};

#endif
