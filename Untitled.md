​        auto animation_object = irisengine::ModelLoader::load("/sdcard/iris/Walk.fbx");

​        if(animation_object){

​            animation_object->setName("WalkingMan");

​            animation_object->setParent(s_scene);

​            auto skel_com = animation_object->getComponent<irisengine::Skeleton>();

​            if(skel_com){

​                auto controller = skel_com->playAnimation("mixamo.com");

​                if (controller) {

​                    controller->setPlaybackSpeed(3.0);

​                    controller->pause();

​                    controller->resume();

​                }

​            }

​        } 