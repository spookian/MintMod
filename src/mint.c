
#define get_weapon_manager weaponManager__Q33scn4step9ComponentFv
#define setup_weapon_desc __ct__Q43scn4step6weapon4DescFQ43scn4step6weapon4KindUlQ43scn4step5ostop4FlagRCQ33hel4math7Vector2RCQ33hel4math7Vector2RQ25ocoll5Owner
#define request_weapon request__Q43scn4step6weapon7ManagerFRCQ43scn4step6weapon4Desc
#define get_hero_objcoll t_obj__Q43scn4step4hero25
#define get_objcoll_owner heapName__Q23mem14HeapCompactionCFRCQ44nrel6devkit7heapmap7HeapMap
#define mint_get_argument_addr internal_getArg_addr__Q26mintvm13MintFuncProxyCFUi
#define mint_add_native_function addNativeFunction__Q26mintvm6VMCoreFPCcPCcPFRQ26mintvm13MintFuncProxy_v
#define destruct_handler __dt__Q24util39ObjRefHandle

#define Owner void
#define WeaponManager void
typedef unsigned long u32;
typedef float Vector2[2];
typedef int WeaponDesc[14];

extern void* get_weapon_manager(void* component_ptr);
extern void request_weapon(int* padding, void *weapon_manager, WeaponDesc weapon_descriptor);
extern void setup_weapon_desc(int* obj, u32 kind, u32 variation, u32 flag, Vector2 position, Vector2 velocity, Owner *owner);
extern void* get_hero_objcoll(void* mint_func_proxy);
extern void* get_objcoll_owner(void* objcoll);
extern u32* mint_get_argument_addr(void* mint_vm, int argument_idx);
extern void mint_add_native_function(void *vm_obj, const char *class_name, const char *funct_definition, u32 funct_addr);

const char *request_definition = "void ReqWeapon(int,int,int,const ref HEL.Math.Vector2,const ref HEL.Math.Vector2)";

void mint_request_projectile(WeaponManager *manager_obj, u32 kind, u32 variation, u32 flag, Vector2 position, Vector2 velocity, Owner *owner);
void mint_wrapper_ReqWeapon(void *mint_vm);
void destruct_handler(int *obj_ref_handle);

void register_ReqWeapon(void *vm_obj, const char *class, const char *funct_definition, u32 funct_addr) // hooks into 804d6660
{
	mint_add_native_function(vm_obj, class, funct_definition, funct_addr);
	mint_add_native_function(vm_obj, class, request_definition, (u32)mint_wrapper_ReqWeapon);
	return;
}

void mint_wrapper_ReqWeapon(void* mint_vm)
{
	u32 kind = *(mint_get_argument_addr(mint_vm, 0));
	u32 variation = *(mint_get_argument_addr(mint_vm, 1));
	u32 flag = *(mint_get_argument_addr(mint_vm, 2));
	Vector2 *pos = (Vector2*)(mint_get_argument_addr(mint_vm, 3)); // these two seem really sketch bc i have no idea if it stores a pointer to a vec2 or a double pointer
	Vector2 *velocity = (Vector2*)(mint_get_argument_addr(mint_vm, 4));
	//FUCK IT.
	Owner *owner = get_objcoll_owner( get_hero_objcoll(mint_vm) );
	WeaponManager *manager = get_weapon_manager((void*)0x809ed018); // there might be a freak accident where this just doesn't work
	
	mint_request_projectile(manager, kind, variation, flag, *pos, *velocity, owner);
	return;
}

void mint_request_projectile(WeaponManager *manager_obj, u32 kind, u32 variation, u32 flag, Vector2 position, Vector2 velocity, Owner *owner)
{
	int padding_data[10];
	WeaponDesc desc_obj;
	setup_weapon_desc(desc_obj, kind, variation, flag, position, velocity, owner);
	
	request_weapon(padding_data, manager_obj, desc_obj);
	destruct_handler(padding_data); // turns out this was very essential
	return;
}