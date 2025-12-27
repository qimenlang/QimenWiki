/** A handle on a resource */

class FrameGraphHandle {





```c++
/** A handle on a resource */
class FrameGraphHandle;
/** A typed handle on a resource */
template<typename RESOURCE>
class FrameGraphId : public FrameGraphHandle;

/** A FrameGraph resource */
struct FrameGraphTexture{
    backend::Handle<backend::HwTexture> handle;
    /** describes a FrameGraphTexture resource */
    struct Descriptor;
    /** Describes a FrameGraphTexture sub-resource */
    struct SubResourceDescriptor;
}



```

