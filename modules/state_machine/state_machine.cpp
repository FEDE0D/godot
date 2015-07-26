
#include "object.h"
#include "state_machine.h"
#include "printf.h"

bool StateMachine::_can_process(){
    return context_id > 0 && current_state_id > 0;
}

State* StateMachine::_get_current_state(){
    if (current_state_id == 0)
        return NULL;

    Object *obj = ObjectDB::get_instance(current_state_id);
    if (obj){
        State *s = obj->cast_to<State>();
        if (s)
            return s;
    }
    return NULL;
}

void StateMachine::_update_cache(){
    this->current_state_id = 0;
    this->context_id = 0;
    if (is_inside_tree()){
        if (has_node(current_state)){
            Node *node = get_node(current_state);
            if (!node || this==node || node->is_a_parent_of(this)) {
                return;
            }
            this->current_state_id = node->get_instance_ID();
        }
        if (has_node(context_node)){
            Node *node = get_node(context_node);
            if (!node)
                return;
            this->context_id = node->get_instance_ID();
        }
    }
}


void StateMachine::set_enabled(bool enabled) {
    this->enabled = enabled;
}

bool StateMachine::is_enabled(){
    return this->enabled;
}

void StateMachine::set_context_node(const NodePath& p_node){
    context_node = p_node;
    context_id = 0;
    if (has_node(context_node)){
        Node *node = get_node(context_node);
        context_id = node->get_instance_ID();
    }
}

NodePath StateMachine::get_context_node(){
    return context_node;
}

void StateMachine::set_current_state(const NodePath& p_node){
    current_state = p_node;
    _update_cache();
}

NodePath StateMachine::get_current_state(){
    return current_state;
}

void StateMachine::change_state(const NodePath& new_state) {
    Node *n = get_node(new_state);
    State *ns = n->cast_to<State>();
    if (ns) {
        _get_current_state()->call("_exit_state");
        set_current_state(new_state);
        _get_current_state()->call("_enter_state");
    }
}

void StateMachine::update_machine(float delta){
    if (enabled && can_process()){
        _get_current_state()->call("_process_state", delta);

        NodePath ns = _get_current_state()->call("_check_state");
        Node *n = get_node(ns);
        if (n){
            State *st = n->cast_to<State>();
            if (st)
                change_state(ns);
        }
    }
}

void StateMachine::_notification(int p_what) {
	switch(p_what) {
        case NOTIFICATION_READY: {
            set_fixed_process(true);
            State *s = _get_current_state();
            if (s)
                s->call("_enter_state");
        } break;
        case NOTIFICATION_FIXED_PROCESS: {
            update_machine(get_fixed_process_delta_time());
		} break;
		case NOTIFICATION_ENTER_TREE: {
            _update_cache();
		} break;
	}
}

void StateMachine::_bind_methods() {

    ObjectTypeDB::bind_method(_MD("set_enabled", "enabled"), &StateMachine::set_enabled);
    ObjectTypeDB::bind_method(_MD("is_enabled"), &StateMachine::is_enabled);
    ADD_PROPERTYNO( PropertyInfo( Variant::BOOL, "enabled"), _SCS("set_enabled"),_SCS("is_enabled"));

    ObjectTypeDB::bind_method(_MD("set_context_node", "context"), &StateMachine::set_context_node);
    ObjectTypeDB::bind_method(_MD("get_context_node"), &StateMachine::get_context_node);
    ADD_PROPERTYNZ( PropertyInfo( Variant::NODE_PATH, "context_path"), _SCS("set_context_node"),_SCS("get_context_node"));

    ObjectTypeDB::bind_method(_MD("set_current_state", "current_state"), &StateMachine::set_current_state);
    ObjectTypeDB::bind_method(_MD("get_current_state"), &StateMachine::get_current_state);
    ADD_PROPERTY( PropertyInfo( Variant::NODE_PATH, "current_state"), _SCS("set_current_state"),_SCS("get_current_state"));

}

StateMachine::StateMachine() {

    enabled = true;

}





