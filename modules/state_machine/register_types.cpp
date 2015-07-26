
#include "register_types.h"
#include "object_type_db.h"
#include "state_machine.h"

void register_state_machine_types(){

    ObjectTypeDB::register_type<State>();
    ObjectTypeDB::register_type<StateMachine>();

}

void unregister_state_machine_types(){  }
