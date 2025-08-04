```c++
const auto geo = CubeGeometry::create();
    auto object = SceneObject::create();
    auto mat = BasicMaterial::create(BasicMaterial::Property::Transparent)->defaultInstance()->duplicate();
    auto renderable = object->addComponent<Renderable>(Renderable::PrimitiveList{{geo, mat}});
    renderable->primitives()[0].material->setParameter("baseColor", color);
    object->setParent(parent);
```





1





