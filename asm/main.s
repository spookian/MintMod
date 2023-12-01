.global __GOLEM_HOOK_START
__GOLEM_HOOK_START:
	lis %r3, (register_ReqWeapon+0x48000001-0x804d6660)@ha
	ori %r3, %r3, (register_ReqWeapon+0x48000001-0x804d6660)@l
	lis %r4, 0x804D
	stw %r3, 0x6660 (%r4)

	b vanilla_start