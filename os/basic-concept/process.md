# 进程

## 进程布局

> 32位Linux内存经典布局

![Layout of 32bit linux process&apos;s memory](../../.gitbook/assets/linux_proc_mm_layout.png)

### Text segment

只读，用于存放代码

### Data segment

所有**有初值**的全局变量，用static修饰的静态变量，静态局部变量

### BSS segment

保存全局/静态未初始化数据

### Heap & Memory Mapping Segment

Heap和bss之前有一个random brk offset，因为如果内存布局按照严格的规则摆放，因此很容易被恶意访问，通过加入随机偏移，使的每个进程的栈空间起始位置都稍有不同，使的被确定栈空间起始位置具有一定难度，防止被恶意访问，这里的random stack offset也是一样.
Heap用于存放动态分配的内存，比如c里的malloc申请的内存，
堆有一个堆指针（break brk），也是按照栈的方式运行的。内存映射段是存在在break brk指针与esp指针之间的一段空间
使用动态分配过程时会根据要分配的内存大小，使用不同的方式。例如在Linux中当动态分配内存大于128K时，会调用mmap函数在esp到break brk之间找一块相应大小的区域作为内存映射段返回给用户，当小于128K时，才会调用brk或者sbrk函数，将break brk向上增长（break brk指针向高地址移动）相应大小，增长出来的区域便作为内存返回给用户。两者的区别是内存映射段销毁时，会释放其映射到的物理内存，而break brk指向的数据被销毁时，不释放其物理内存，只是简单将break brk回撤，其虚拟地址到物理地址的映射依旧存在，这样使的当再需要分配小额内存时，只需要增加break brk的值，由于这段虚拟地址与物理地址的映射还存在，于是不会触发缺页中断。只有在break brk减少足够多，占据物理内存的空闲虚拟内存足够多时，才会真正释放它们

### Stack

所有的局部变量都存储在这里且函数的运行也需要栈，需要注意的是上面是栈底下面是栈顶，栈空间大小是一个固定的值，例如4K、8K之类的。但是可以调整其大小，例如在进程中通过改变setrlimit函数的RLIMIT_STACK来调整其大小
嵌套函数调用有层数限制，每当发生一次函数调用时，首先将当前地址压栈，再将函数的参数分别压栈，然后跳转到函数内代码处开始执行，在函数执行结束时，函数的参数分别出栈，再弹出原先压栈的地址，这样就能跳转回函数调用完毕后的代码处了
栈空间有对应的栈指针（esp）。栈指针表示当前栈用了多少空间。例如，当压栈新的数据时，栈指针便向下增长（esp指针向低地址移动），栈指针到栈空间起始处的内存区域不得大于栈空间大小限制

### kernel space
[链接](https://zhuanlan.zhihu.com/p/68501351)

### 其他
[32-linux](https://www.arm.linux.org.uk/developer/memory.txt)

[64-linux](https://www.kernel.org/doc/Documentation/x86/x86_64/mm.txt)