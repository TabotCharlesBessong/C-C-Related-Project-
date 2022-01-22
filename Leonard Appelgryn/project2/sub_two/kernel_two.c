#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <asm/uaccess.h>
#include <linux/slab.h>
#include <linux/seq_file.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/sched.h>


static char *str = NULL;



//Show prof file
static int show_proc(struct seq_file *m,void *v){
	seq_printf(m,"%s\n",str);
	return 1;
}


//write to proc file
static ssize_t write_to_proc(struct file* file,const char __user *buffer,size_t count,loff_t *f_pos){
	char *tmp = kzalloc((count+1),GFP_KERNEL);
	if(!tmp)return -ENOMEM;
	if(copy_from_user(tmp,buffer,count)){
		kfree(tmp);
		return EFAULT;
	}
	kfree(str);
	str=tmp;
	return count;
}

//Open proc file
static int open_proc(struct inode *inode,struct file *file){
	return single_open(file,show_proc,NULL);
}


//Structure defines all operations to be carried out on proc file created by module
static struct file_operations my_fops={
	.owner = THIS_MODULE,
	.open = open_proc,
	.release = single_release,
	.read = seq_read,
	.llseek = seq_lseek,
	.write = write_to_proc
};

//Create kernel module that will eventually create proc file
    int proc_init(void){
    struct proc_dir_entry *entry;
	entry = proc_create("seconds",0777,NULL,&my_fops);
	if(!entry){
		return -1;	
	}else{
		printk(KERN_INFO "Hurray! Successfully created proc file\n");
	}
	return 0;
}

//Delete kernel module that creates proc file
 void delete_proc_exit(void){
    remove_proc_entry("seconds",NULL);
    printk(KERN_INFO "Cleaning up module.\n");
}

module_init(proc_init);
module_exit(delete_proc_exit);

//Module Info
MODULE_LICENSE("GPL");
MODULE_AUTHOR("YIMNAI NERUS ZAUMU");
MODULE_DESCRIPTION("This module creates a proc file called seconds.\nIt returns the number of seconds since the\nfile was loading unto memory.");
