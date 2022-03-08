#include <linux/build-salt.h>
#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(.gnu.linkonce.this_module) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used __section(__versions) = {
	{ 0xb3753869, "module_layout" },
	{ 0x3700313a, "single_release" },
	{ 0x4e22ab94, "seq_read" },
	{ 0xf77b56e2, "seq_lseek" },
	{ 0xa3ee9e12, "remove_proc_entry" },
	{ 0xc5850110, "printk" },
	{ 0xdb59a12d, "proc_create" },
	{ 0x37a0cba, "kfree" },
	{ 0x362ef408, "_copy_from_user" },
	{ 0x88db9f48, "__check_object_size" },
	{ 0xeb233a45, "__kmalloc" },
	{ 0xd981b7ff, "seq_printf" },
	{ 0xf6fa2eb9, "single_open" },
	{ 0xbdfb6dbb, "__fentry__" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "9C70F6FD449733FC4AAB846");
