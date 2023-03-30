## Allocate and reclaim app memory

The Dalvik heap is constrained to a single virtual memory range for each app process. This defines the logical heap size, which can grow as it needs to but only up to a limit that the system defines for each app.

The logical size of the heap is not the same as the amount of physical memory used by the heap. When inspecting your app's heap, Android computes a value called the Proportional Set Size (PSS), which accounts for both dirty and clean pages that are shared with other processes—but only in an amount that's proportional to how many apps share that RAM. This (PSS) total is what the system considers to be your physical memory footprint. For more information about PSS, see the [Investigating Your RAM Usage](https://developer.android.com/studio/profile/investigate-ram) guide.

The Dalvik heap does not compact the logical size of the heap, meaning that Android does not defragment the heap to close up space. Android can only shrink the logical heap size when there is unused space at the end of the heap. However, the system can still reduce physical memory used by the heap. After garbage collection, Dalvik walks the heap and finds unused pages, then returns those pages to the kernel using madvise. So, paired allocations and deallocations of large chunks should result in reclaiming all (or nearly all) the physical memory used. However, reclaiming memory from small allocations can be much less efficient because the page used for a small allocation may still be shared with something else that has not yet been freed.

### 内存分配

1. 内存分配系统调用
   - brk：数据段的最高地址指针_edata往高地址位增长；在
   - mmap : 物理空间内存页到虚拟空间的映射，堆和栈之间的空间的一块空闲地址；
   - 如果请求分配的内存空间大于128k(M_MMAP_THRESHOLD可调节)，则在mmap上分配；
2. 内存碎片产生的原因：brk分配的内存需要等到高位地址内存释放之后才能释放，这就是内存碎片产生的原因；mmap分配的内存可以单独释放；
3. 内碎片外碎片
   - 内碎片，采用分区存储管理
     - 分页存储管理
     - 分段存储管理
     - 段页存储管理
   - 外碎片,采用冒泡的方式，进行内存碎片整理；
4. 