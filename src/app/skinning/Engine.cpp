#include "Core.h"
#include "Engine.h"

#include <iostream>
#include <unistd.h>
#include <GL/gl.h>

using namespace sleek;
using namespace device;

namespace sample
{
    void define_cylinder_bone(Skinning *mesh)
    {
        std::cout << "setup cylinder bones" << std::endl;
        
        mesh->parent.push_back(-1);
        mesh->parent.push_back(-1);
        mesh->handle.push_back(glm::vec3(25,0,0));
        mesh->handle.push_back(glm::vec3());
        mesh->current.rotation.push_back(glm::vec3(0,0,0));
        mesh->current.rotation.push_back(glm::vec3(0,0,0));
        mesh->current.translation.push_back(glm::vec3(0,0,0));
        mesh->current.translation.push_back(glm::vec3(0,0,0));
        mesh->current.scale.push_back(glm::vec3(1, 0.25, 1));
        mesh->current.scale.push_back(glm::vec3(1, 0.25, 1));
        
        auto &weight = mesh->weight;
        auto &boneid = mesh->boneid;
        
        sleek::math::vec4f displacement(0.12f);

        for(int i = 0; i<weight.size(); ++i)
        {
            float coef = mesh->getptr()->vertices[i].Coord.x;
            weight[i]  = sleek::math::vec4f(coef, 0.f, 1.f-coef, 0.f);
            weight[i]  = glm::clamp(weight[i], displacement, 1.f-displacement);
            weight[i] -= displacement.x;
            boneid[i]  = sleek::math::vec4c(0,0,1,0);
        }
        
        for(int i = 0; i<weight.size(); ++i)
            weight[i] /= weight[i].x+weight[i].y+weight[i].z+weight[i].w;
    }
    
    float atan2(float y, float x)
    {
        float s = float(abs(x) > abs(y));
        float a = 3.14159265359/2.0 - std::atan2(x,y);
        float b = std::atan2(y,x);
        return a*s + b*(1-s);
    }
    
    void define_heart_bone(Skinning *mesh)
    {
        std::cout << "setup cylinder bones" << std::endl;
        
        mesh->parent.push_back(-1);
        mesh->parent.push_back(-1);
        mesh->handle.push_back(glm::vec3(25,0,0));
        mesh->handle.push_back(glm::vec3());
        mesh->current.rotation.push_back(glm::vec3(0,0,0));
        mesh->current.rotation.push_back(glm::vec3(0,0,0));
        mesh->current.translation.push_back(glm::vec3(0,0,0));
        mesh->current.translation.push_back(glm::vec3(0,0,0));
        mesh->current.scale.push_back(glm::vec3(1, 0.25, 1));
        mesh->current.scale.push_back(glm::vec3(1, 0.25, 1));
        
        auto &weight = mesh->weight;
        auto &boneid = mesh->boneid;
        
        sleek::math::vec4f displacement(-0.3);
        for(int i = 0; i<weight.size(); ++i)
        {
            auto coef = glm::normalize(mesh->getptr()->vertices[i].Pos);
            float uvx = 0.5 - atan2(coef.z, coef.x) / 3.14159265359 / 2.0;
            float uvy = 0.5 - coef.z * 0.5;
            
            weight[i]  = sleek::math::vec4f(uvx, 1.f-uvy, 0.f, 0.f);
            weight[i]  = glm::clamp(weight[i], displacement, 1.f-displacement);
            weight[i] -= displacement.x;
            boneid[i]  = sleek::math::vec4c(0,1,0,1);
        }
        
        for(int i = 0; i<weight.size(); ++i)
            weight[i] /= weight[i].x+weight[i].y+weight[i].z+weight[i].w;
    }
    
    void animate_cylinder_bone(Skinning *mesh, float time)
    {
        float mov1 = -std::max(0.f, 2*sin(time/20.f));
        float mov2 =  std::max(0.f,-2*sin(time/20.f));
        float scl  = 0.1f + 0.75*std::abs(cos(time/5.f));

        Skinning::Bone first = mesh->getBone(0);
        Skinning::Bone second = mesh->getBone(1);

        first.rotation     = {0,1.3f*mov1,0};
        first.translation  = {-5.f*mov2,0,0};
        first.scale        = {1, scl, 1};

        second.rotation    = {1.4f*mov2,0,0};
        second.translation = {5.f*mov2,0,0};
        second.scale       = {1, scl, 1};
    }
    
    void animate_heart_bone(Skinning *mesh, float time)
    {
        float mov2 = 0.2*sin(time/5.f);
        float mov1 = 0.1*cos(time/5.f);
        
        float scl1 = 0.8f + 0.2*std::max(0.0f, sin( time/5.f));
        float scl2 = 0.8f + 0.2*std::max(0.0f, sin(-time/5.f));

        Skinning::Bone first = mesh->getBone(0);
        Skinning::Bone second = mesh->getBone(1);

        first.scale        = {1, scl1, 1};
        first.translation  = {0, mov1, 0};

        second.scale       = {1, scl2, 1};
        second.translation = {0, mov2, mov1};
    }

    Engine::Engine(Core *mom) noexcept
        : screen(mom->getDevice()), core(mom),
          rotation(true), distance(100), rot(-32*5), pitch(3*5),
          linear_blend(std::shared_ptr<driver::mesh>(driver::Geometry().createCylindre(10.f, 100.f, 40.f, 100.f)), &define_cylinder_bone),
          dual_quat(std::shared_ptr<driver::mesh>(driver::Geometry().createCylindre(10.f, 100.f, 40.f, 100.f)), &define_cylinder_bone),
          heart(mom->getLoader()->loadMesh("mesh/heart.obj"), &define_heart_bone)
    {
        smgr = new sleek::scene3d::Scene(screen, mom->getDriver());

        linear_blend.setAnimationCallback(animate_cylinder_bone);
        dual_quat.setAnimationCallback(animate_cylinder_bone);
        heart.setAnimationCallback(animate_heart_bone);

        texture.push_back(mom->getLoader()->loadTexture("texture/crate.jpg"));
        texture.push_back(mom->getLoader()->loadTexture("texture/crate.jpg"));
        texture.push_back(mom->getLoader()->loadTexture("texture/flesh.jpg"));
//        texture.push_back(mom->getLoader()->loadTexture("texture/metal.blp"));

        for(auto &it : texture)
        {
            if(!it) continue;
            it->createIdentifier(mom->getContext());
            it->getIdentifier()->update();
        }
        
        core->getContext()->createVAO(*linear_blend, sleek::driver::VAO_STATIC, sleek::driver::VAO_STATIC);
        core->getContext()->createVAO(*dual_quat, sleek::driver::VAO_STATIC, sleek::driver::VAO_STATIC);

        grid = new scene3d::real::Grid(smgr);
        grid->setPosition({0,-50,0});
        grid->setMaterial(buildMaterial(
            grid, nullptr,
            "shader/object/default.vert",
            "shader/object/solid.frag",
            callback, 0
        ));
        smgr->addSceneNode(grid);

        //! Linear Blend Skinning over GPU

        node.push_back(new scene3d::real::Natif(smgr));
        node[0]->setPosition({0,50,0});
        node[0]->setMaterial(buildMaterial(
            node[0], &linear_blend,
            "shader/object/linear_blend.vert",
            "shader/object/solid.frag",
            LinearBlend::shader_callback, 1
        ));
        node[0]->setMesh(linear_blend.getptr());
        smgr->addSceneNode(node[0]);

        //! Dual Quaternion Skinning over GPU

        node.push_back(new scene3d::real::Natif(smgr));
        node[1]->setPosition({0,25,0});
        node[1]->setMaterial(buildMaterial(
            node[1], &dual_quat,
            "shader/object/dual_quaternion.vert",
            "shader/object/solid.frag",
            DualQuaternion::shader_callback, 1
        ));
        
        node[1]->setMesh(dual_quat.getptr());
        smgr->addSceneNode(node[1]);

        //! Append shared mesh momory for CPU skinning

        mesh.push_back(std::make_shared<driver::mesh>());
        mesh.push_back(std::make_shared<driver::mesh>());
        core->getContext()->createVAO(mesh[0].get(), sleek::driver::VAO_STREAM, sleek::driver::VAO_STREAM);
        core->getContext()->createVAO(mesh[1].get(), sleek::driver::VAO_STREAM, sleek::driver::VAO_STREAM);

        //! Linear Blend Skinning over CPU

        node.push_back(new scene3d::real::Natif(smgr));
        node[2]->setPosition({0,0,0});
        node[2]->setMaterial(buildMaterial(
            node[2], &mesh[0],
            "shader/object/default.vert",
            "shader/object/solid.frag",
            Skinning::shader_callback, 1
        ));
        node[2]->setMesh(mesh[0]->getptr());
        smgr->addSceneNode(node[2]);

        //! Dual Quaternion Skinning over CPU

        node.push_back(new scene3d::real::Natif(smgr));
        node[3]->setPosition({0,-25,0});
        node[3]->setMaterial(buildMaterial(
            node[3], &mesh[1],
            "shader/object/default.vert",
            "shader/object/solid.frag",
            Skinning::shader_callback, 1
        ));
        node[3]->setMesh(mesh[1]->getptr());
        smgr->addSceneNode(node[3]);

        //! Dual Quaternion Skinning over CPU

        core->getContext()->createVAO(*heart, sleek::driver::VAO_STATIC, sleek::driver::VAO_STATIC);
        node.push_back(new scene3d::real::Natif(smgr));
        node[4]->setPosition({0,15,0});
        node[4]->setScale({50,50,50});
        node[4]->setMaterial(buildMaterial(
            node[4], &heart,
            "shader/object/dual_quaternion.vert",
            "shader/object/solid.frag",
            DualQuaternion::shader_callback, 2
        ));
        node[4]->setEnable(false);
        node[4]->setMesh(heart.getptr());
        smgr->addSceneNode(node[4]);

        smgr->getCamera()->setRotation({0, 1, 0});
        smgr->getCamera()->setTarget({0, 0, 0});
    }

    Engine::~Engine() noexcept
    {
        smgr->clear();
    }

    std::shared_ptr<sleek::driver::material> Engine::buildMaterial(
        sleek::scene3d::Node *node, void *user,
        std::string filename_vert, std::string filename_frag,
        sleek::driver::shader_callback callback, int tid
    ) noexcept
    {
        auto shade = core->getContext()->createShader();
        auto mat = std::make_shared<driver::material>();

        mat->setMode(driver::rmd_polygon);
        mat->setShadeModel(driver::rsd_flat);
//        mat->setFaceCulling(driver::rfc_back);
        mat->setMaterialRender(driver::rmt_solid);
        mat->setShader(shade);

        if(tid >= 0 && tid < texture.size() && texture[tid])
            mat->Texture.push_back(texture[tid]->getIdentifier().get());

        auto vert = core->getFileSystem()->read(filename_vert);
        auto frag = core->getFileSystem()->read(filename_frag);

        shade->attacheShader(driver::shd_vert, vert->readAll(), "main");
        shade->attacheShader(driver::shd_frag, frag->readAll(), "main");
        // used to get information from material (like texture binding) by callback
        shade->setLinkToMaterial(mat.get());
        // used to get model view
        shade->user[0] = node;
        shade->user[1] = user;

        shade->compileShader();
        shade->setCallback(callback);

        return mat;
    }

    bool Engine::manage(sleek::device::input *a) noexcept
    {
        if(smgr->manage(a))
            return true;

        if(a->type == EVENT_MOUSSE_UP)
        {
            if(a->mouse[MOUSE_WHEEL_DOWN])
            {
                distance *= 1.25;
                return true;
            }
            if(a->mouse[MOUSE_WHEEL_UP])
            {
                distance *= 0.75;
                return true;
            }
        }

        if(a->type == EVENT_KEY_DOWN)
        {
            //! engine test
            if(a->key[KEY_F11])
            {
                screen->setFullScreen(!screen->getInfo().fullscreen);
                return true;
            }

            //! engine test
            if(a->key[KEY_SPACE])
            {
                rotation = !rotation;
                return true;
            }

            //! camera

            if(a->key[KEY_LEFT])
            {
                rot -= 5.f;
                return true;
            }
            if(a->key[KEY_RIGHT])
            {
                rot += 5.f;
                return true;
            }
            if(a->key[KEY_DOWN])
            {
                pitch -= 5;
                return true;
            }
            if(a->key[KEY_UP])
            {
                pitch += 5;
                return true;
            }
            
            //! object enable/disable
            
            if(a->key[KEY_KEY_A])
            {
                for(int i = 0; i<node.size()-1; ++i)
                    node[i]->setEnable(!node[i]->getEnable());
                return true;
            }
            if(a->key[KEY_KEY_Z])
            {
                node[node.size()-1]->setEnable(!node[node.size()-1]->getEnable());
                return true;
            }

            //! render

            if(a->key[KEY_KEY_W])
            {
                for(auto &it : node)
                {
                    it->getMaterial()->setWireframe(
                        !it->getMaterial()->getWireframe()
                    );
                }
                grid->setEnable(!grid->getEnable());
                return true;
            }

            if(a->key[KEY_KEY_S])
            {
                return true;
            }
        }

        return false;
    }

    void Engine::render() noexcept
    {
        float time = tm.getTimeMsec()/50.0f;

        if(rotation)
        {
            tm.update();

            if(node[2]->getEnable())
            {
                linear_blend.animate(time);
                linear_blend.getCurrentFrame(mesh[0]);
            }
                
            if(node[3]->getEnable())
            {
                dual_quat.animate(time);
                dual_quat.getCurrentFrame(mesh[1]);
            }
                
            if(node[4]->getEnable())
                heart.animate(time);
        }

        smgr->getCamera()->setTarget({0, 15, 0});

        sleek::math::vec4f camera(distance, 0, 0, 1);
        sleek::math::mat4f transform  = glm::toMat4(sleek::math::quatf(glm::vec3(0.0f, rot/100, 0.0f)));
                           transform *= glm::toMat4(sleek::math::quatf(glm::vec3(0.0f, 0.0f, pitch/100)));
        camera = transform * camera;

        smgr->getCamera()->setPosition(sleek::math::vec3f(camera.x, camera.y, camera.z));

        smgr->render();
    }
}
