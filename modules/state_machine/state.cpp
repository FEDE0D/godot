
#include "object.h"
#include "state.h"
#include "state_machine.h"

Node* State::get_context(){
    //TODO fix this!
    Node *np = get_parent();
    if (np){
        StateMachine *sm = np->cast_to<StateMachine>();
        if (sm)
            return sm->get_node(sm->get_context_node());
    }
}

void State::_bind_methods() {
    BIND_VMETHOD( MethodInfo("_enter_state"));
    BIND_VMETHOD( MethodInfo("_exit_state"));
    BIND_VMETHOD( MethodInfo("_check_state"));
    BIND_VMETHOD( MethodInfo("_process_state", PropertyInfo(Variant::REAL,"delta")) );

    ObjectTypeDB::bind_method(_MD("get_context"), &State::get_context);
}

State::State() {

}



