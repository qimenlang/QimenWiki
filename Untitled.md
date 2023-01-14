​    auto addSphere = [&](const glm::vec3& v){

​        auto sphere = SceneObject::create();

​        sphere->setName("sphere");

​        sphere->setPosition(v);

​        sphere->setScale(glm::vec3{0.8});

​        sphere->setRotation(glm::quat(glm::radians(glm::vec3{30.f, 30.f, 0})));

​        auto sgeo = SphereGeometry::getDefault();

​        sphere->addComponent(Renderable::create({{sgeo, mat}}));

​        auto sphereRenderable = sphere->getComponent<Renderable>();

​        sphereRenderable->setCastShadows(true);

​        sphere->setParent(scene);        

​    };



​    addSphere({0.0,0.0,-0.0});

​    addSphere({1.0,0.0,-0.0});

​    addSphere({2.0,0.0,-0.0});

​    addSphere({3.0,0.0,-0.0});

​    addSphere({4.0,0.0,-0.0});





​    addSphere({0.0,1.0,-0.0});

​    addSphere({0.0,2.0,-0.0});

​    addSphere({0.0,3.0,-0.0});

​    addSphere({0.0,4.0,-0.0});



​    addSphere({0.0,0.0,-1.0});

​    addSphere({0.0,0.0,-2.0});

​    addSphere({0.0,0.0,-3.0});

​    addSphere({0.0,0.0,-4.0});

​    addSphere({0.0,0.0,-5.0});

​    addSphere({0.0,0.0,-6.0});

​    addSphere({-1.0,0.0,-7.0});



​    addSphere({1.0,1.0,-0.0});

​    addSphere({2.0,2.0,-0.0});

​    addSphere({3.0,3.0,-0.0});

​    addSphere({4.0,4.0,-0.0});