# 进程

## 进程布局

> 32位Linux内存经典布局

![Layout of 32bit linux process&apos;s memory](../../.gitbook/assets/linux_proc_mm_layout.png)

### **Text segment**

只读，用于存放代码

### Data segment

所有**有初值**的全局变量，用static修饰的静态变量，静态局部变量

### BSS segment

保存全局/静态未初始化数据

### Heap & Memory Mapping Segment

Heap下面有一个



