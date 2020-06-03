#include <linux/module.h>
#include <linux/sched.h>
#include <linux/pid.h>
#include <linux/kthread.h>
#include <linux/kernel.h>
#include <linux/err.h>
#include <linux/slab.h>
#include <linux/printk.h>
#include <linux/jiffies.h>
#include <linux/kmod.h>
#include <linux/fs.h>
#include <linux/wait.h>

MODULE_LICENSE("GPL");

struct wait_opts {
    enum pid_type        wo_type;
    int            wo_flags;
    struct pid        *wo_pid;
    
    struct siginfo __user    *wo_info;
    int __user        *wo_stat;
    struct rusage __user    *wo_rusage;
    
    wait_queue_t        child_wait;
    int            notask_error;
};

extern long do_wait(struct wait_opts *wo);

//implement exec function
int my_exec(void){
    /* execute a test program in child process */
    int result;
    const char path[] = "/home/seed/Documents/program2/test";
    const char *const argv[] = {path, NULL, NULL};
    const char *const envp[] = {"Home=/", "PATH=/sbin:/user/sbin:/bin:/user/bin", NULL};
    
    struct filename * my_filename = getname(path);
    printk("[program2] : child process\n");
    result = do_execve(my_filename, argv, envp);

    if(!result)
        return 0;
    do_exit(result);
}

//implement wait function
void my_wait(pid_t pid){
    
    int status;
    struct wait_opts wo;
    struct pid *wo_pid = NULL;
    enum pid_type type;
    type = PIDTYPE_PID;
    wo_pid = find_get_pid(pid);
    
    wo.wo_type = type;
    wo.wo_pid = wo_pid;
    wo.wo_flags = WEXITED;
    wo.wo_info = NULL;
    wo.wo_stat = (int __user*)&status;
    wo.wo_rusage = NULL;
    
    int a;
    a = do_wait(&wo);
//    printk("do_wait return value is %d\n", &a);
    
    // output child process exit status

    switch (*wo.wo_stat) {
        case 7:{
            printk("[program2] : get SIGBUS signal\n");
            printk("[program2] : child process has bus error\n");
            printk("[program2] : The return signal is %d\n", *wo.wo_stat);
            break;
        }
        case 1:{
            printk("[program2] : get SIGHUP signal\n");
            printk("[program2] : The return signal is %d\n", *wo.wo_stat);
            break;
        }
        case 2:{
            printk("[program2] : get SIGINT signal\n");
            printk("[program2] : The return signal is %d\n", *wo.wo_stat);
            break;
        }
        case 3:{
            printk("[program2] : get SIGQUIT signal\n");
            printk("[program2] : The return signal is %d\n", *wo.wo_stat);
            break;
        }
        case 4:{
            printk("[program2] : get SIGILL signal\n");
            printk("[program2] : The return signal is %d\n", *wo.wo_stat);
            break;
        }
        case 5:{
            printk("[program2] : get SIGTRAP signal\n");
            printk("[program2] : The return signal is %d\n", *wo.wo_stat);
            break;
        }
        case 6:{
            printk("[program2] : get SIGABRT signal\n");
            printk("[program2] : The return signal is %d\n", *wo.wo_stat);
            break;
        }
        case 8:{
            printk("[program2] : get SIGFPE signal\n");
            printk("[program2] : The return signal is %d\n", *wo.wo_stat);
            break;
        }
        case 9:{
            printk("[program2] : get SIGKILL signal\n");
            printk("[program2] : The return signal is %d\n", *wo.wo_stat);
            break;
        }
        case 11:{
            printk("[program2] : get SIGSEGV signal\n");
            printk("[program2] : The return signal is %d\n", *wo.wo_stat);
            break;
        }
        case 13:{
            printk("[program2] : get SIGPIPE signal\n");
            printk("[program2] : The return signal is %d\n", *wo.wo_stat);
            break;
        }
        case 14:{
            printk("[program2] : get SIGALRM signal\n");
            printk("[program2] : The return signal is %d\n", *wo.wo_stat);
            break;
        }
        case 15:{
            printk("[program2] : get SIGTERM signal\n");
            printk("[program2] : The return signal is %d\n", *wo.wo_stat);
            break;
        }
        case 19:{
            printk("[program2] : get SIGSTOP signal\n");
            printk("[program2] : The return signal is %d\n", *wo.wo_stat);
            break;
        }
            
        default:
            break;
    }
    
    put_pid(wo_pid);
    return;
}


//implement fork function
int my_fork(void *argc){
    
    pid_t pid;
    //set default sigaction for current process
    int i;
    struct k_sigaction *k_action = &current->sighand->action[0];
    for(i=0;i<_NSIG;i++){
        k_action->sa.sa_handler = SIG_DFL;
        k_action->sa.sa_flags = 0;
        k_action->sa.sa_restorer = NULL;
        sigemptyset(&k_action->sa.sa_mask);
        k_action++;
    }
    
    /* fork a process using do_fork */
    pid = _do_fork(SIGCHLD, (unsigned long)&my_exec, 0, NULL, NULL, 0);
    printk("[program2] : The child process has pid = %d\n", pid);
    printk("[program2] : This is the parent process, pid = %d\n", (int)current->pid);
    
    /* wait until child process terminates */
    my_wait(pid);
    return 0;
}

static int __init program2_init(void){
    
    printk("[program2] : Module_init\n");
    
    /* write your code here */
    printk("[program2] : Module_init create kthread\n");
    /* create a kernel thread to run my_fork */
    struct task_struct *task;
    task = kthread_create(&my_fork, NULL, "MyThread");
    
    if (!IS_ERR(task)) {
        printk("[program2] : Module_init kthread start");
        wake_up_process(task);
    }
    return 0;
}

static void __exit program2_exit(void){
    printk("[program2] : Module_exit\n");
}

module_init(program2_init);
module_exit(program2_exit);
