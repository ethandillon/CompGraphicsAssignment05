

#include <ctime>
#include <cmath>
#include "GLM/gtc/type_ptr.hpp"
#include <glad/gl.h>

#include "learnopengl/shader_4722.h"
#include "cs4722/artifact.h"
#include "cs4722/view.h"
#include "cs4722/shape.h"
#include "cs4722/buffer_utilities.h"
#include "cs4722/window.h"

//#define LOG_FLUP 1

static cs4722::View *the_view;
static Shader *shader;
static std::vector<cs4722::Artifact*> artf_list;

static cs4722::HeightFieldFNL *terrain_height_field;
static cs4722::Shape* terrain_shape;
static glm::vec3 terrain_scale = glm::vec3(100, 10, 100);
static glm::vec3 terrain_translate = glm::vec3(0,0,0);
static bool movement_restricted = true;
static double max_height = .9 * terrain_scale.y + terrain_translate.y;

void init()
{
    the_view = new cs4722::View();

    shader = new Shader("vertex_shader.glsl","fragment_shader.glsl");
    shader->use();

    glEnable(GL_DEPTH_TEST);

    auto terrain_height_field_granularity = 200;
    terrain_height_field = new cs4722::HeightFieldFNL(terrain_height_field_granularity, terrain_height_field_granularity);
    terrain_height_field->frequency = 1.5;
    // terrain_height_field->seed = 12345; //  fractal selector 0    noise selector 0
    terrain_height_field->seed = 121; //  fractal selector 1    noise selector 0
    // terrain_height_field->seed = 70; //  fractal selector 3    noise selector 0
    // terrain_height_field->seed = 11; //  fractal selector 2    noise selector 0
    // terrain_height_field->seed = clock();
    srand(terrain_height_field->seed);

    auto fractal_type_selector = rand() % 6;
    std::cout << "Fractal type selector " <<  fractal_type_selector << std::endl;
    switch (fractal_type_selector) {
        case 0: terrain_height_field->fractalType = FastNoiseLite::FractalType_None;
            break;
        case 1: terrain_height_field->fractalType = FastNoiseLite::FractalType_FBm;
            break;
        case 2: terrain_height_field->fractalType = FastNoiseLite::FractalType_Ridged;
            break;
        case 3: terrain_height_field->fractalType = FastNoiseLite::FractalType_PingPong;
            break;
        case 4: terrain_height_field->fractalType = FastNoiseLite::FractalType_DomainWarpProgressive;
            break;
        case 5: terrain_height_field->fractalType = FastNoiseLite::FractalType_DomainWarpIndependent;
            break;
    }
    auto noise_type_selector = rand() % 6;
    std::cout << "Noise type selector " <<  noise_type_selector << std::endl;
    switch (noise_type_selector) {
        case 0: terrain_height_field->noiseType = FastNoiseLite::NoiseType_OpenSimplex2;
            break;
        case 1: terrain_height_field->noiseType = FastNoiseLite::NoiseType_OpenSimplex2S;
            break;
        case 2: terrain_height_field->noiseType = FastNoiseLite::NoiseType_Cellular;
            break;
        case 3: terrain_height_field->noiseType = FastNoiseLite::NoiseType_Perlin;
            break;
        case 4: terrain_height_field->noiseType = FastNoiseLite::NoiseType_ValueCubic;
            break;
        case 5: terrain_height_field->noiseType = FastNoiseLite::NoiseType_Value;
            break;
    }
    terrain_height_field->numberOfOctaves = 4;
//    terrain_height_field->ping_pong_strength = 7;
    terrain_height_field->generate();
    terrain_shape = new cs4722::Terrain(terrain_height_field);

    auto* artf = new cs4722::Artifact();
    artf->theShape = terrain_shape;

    artf->worldTransformation->multiplyScale(terrain_scale);
    artf->worldTransformation->multiplyTranslation(terrain_translate);
    artf_list.push_back(artf);

    terrain_height_field->scale = terrain_scale;
    terrain_height_field->translate = terrain_translate;

    // Create and place artifacts on the terrain
    // Each artifact will be placed at different positions on the terrain    // Cube artifact at position (20, ?, 20)
    auto* cube_rotating_transform = new cs4722::TransformationAnimationRotating();
    cube_rotating_transform->rotationRate = 7.5 * 2.0 * M_PI / 60.0; // 7.5 rotations per minute in radians per second
    cube_rotating_transform->rotationAxis = glm::vec3(0, 1, 0); // rotate about Y axis
    float cube_x = 20.0f, cube_z = 20.0f;
    float cube_terrain_height = terrain_height_field->altitude(cube_x, cube_z);
    cube_rotating_transform->rotationCenter = glm::vec3(cube_x, cube_terrain_height + 2.0f, cube_z);
    auto* cube_artifact = new cs4722::Artifact(cube_rotating_transform);
    cube_artifact->theShape = new cs4722::Block();
    cube_artifact->worldTransformation->multiplyScale(glm::vec3(2.0f, 4.0f, 2.0f)); // width 2, height 4, depth 2
    cube_artifact->worldTransformation->multiplyTranslation(glm::vec3(cube_x, cube_terrain_height + 2.0f, cube_z)); // +2 to center it above ground
    artf_list.push_back(cube_artifact);    // Cylinder artifact at position (80, ?, 30)
    auto* cylinder_rotating_transform = new cs4722::TransformationAnimationRotating();
    cylinder_rotating_transform->rotationRate = 7.5 * 2.0 * M_PI / 60.0; // 7.5 rotations per minute in radians per second
    cylinder_rotating_transform->rotationAxis = glm::vec3(0, 1, 0); // rotate about Y axis
    float cyl_x = 80.0f, cyl_z = 30.0f;
    float cyl_terrain_height = terrain_height_field->altitude(cyl_x, cyl_z);
    cylinder_rotating_transform->rotationCenter = glm::vec3(cyl_x, cyl_terrain_height + 2.0f, cyl_z);
    auto* cylinder_artifact = new cs4722::Artifact(cylinder_rotating_transform);
    cylinder_artifact->theShape = new cs4722::Cylinder();
    cylinder_artifact->worldTransformation->multiplyScale(glm::vec3(2.0f, 4.0f, 2.0f)); // width 2, height 4, depth 2
    cylinder_artifact->worldTransformation->multiplyTranslation(glm::vec3(cyl_x, cyl_terrain_height + 2.0f, cyl_z)); // +2 to center it above ground
    artf_list.push_back(cylinder_artifact);    // Sphere artifact at position (30, ?, 70)
    auto* sphere_rotating_transform = new cs4722::TransformationAnimationRotating();
    sphere_rotating_transform->rotationRate = 7.5 * 2.0 * M_PI / 60.0; // 7.5 rotations per minute in radians per second
    sphere_rotating_transform->rotationAxis = glm::vec3(0, 1, 0); // rotate about Y axis
    float sphere_x = 30.0f, sphere_z = 70.0f;
    float sphere_terrain_height = terrain_height_field->altitude(sphere_x, sphere_z);
    sphere_rotating_transform->rotationCenter = glm::vec3(sphere_x, sphere_terrain_height + 2.0f, sphere_z);
    auto* sphere_artifact = new cs4722::Artifact(sphere_rotating_transform);
    sphere_artifact->theShape = new cs4722::Sphere();
    sphere_artifact->worldTransformation->multiplyScale(glm::vec3(2.0f, 4.0f, 2.0f)); // width 2, height 4, depth 2
    sphere_artifact->worldTransformation->multiplyTranslation(glm::vec3(sphere_x, sphere_terrain_height + 2.0f, sphere_z)); // +2 to center it above ground
    artf_list.push_back(sphere_artifact);    // Torus artifact at position (70, ?, 80)
    auto* torus_rotating_transform = new cs4722::TransformationAnimationRotating();
    torus_rotating_transform->rotationRate = 7.5 * 2.0 * M_PI / 60.0; // 7.5 rotations per minute in radians per second
    torus_rotating_transform->rotationAxis = glm::vec3(0, 1, 0); // rotate about Y axis
    float torus_x = 70.0f, torus_z = 80.0f;
    float torus_terrain_height = terrain_height_field->altitude(torus_x, torus_z);
    torus_rotating_transform->rotationCenter = glm::vec3(torus_x, torus_terrain_height + 2.0f, torus_z);
    auto* torus_artifact = new cs4722::Artifact(torus_rotating_transform);
    torus_artifact->theShape = new cs4722::Torus();
    torus_artifact->worldTransformation->multiplyScale(glm::vec3(2.0f, 4.0f, 2.0f)); // width 2, height 4, depth 2
    torus_artifact->worldTransformation->multiplyTranslation(glm::vec3(torus_x, torus_terrain_height + 2.0f, torus_z)); // +2 to center it above ground
    artf_list.push_back(torus_artifact);

    // auto lp = terrain_height_field->low_point();
    the_view->cameraPosition = terrain_height_field->low_point() + glm::vec4(0,1,0,0);

    cs4722::initBuffers(shader->ID, artf_list, "b_position", "b_color");
}



void render()
{
    auto view_transform = glm::lookAt(the_view->cameraPosition,
                                      the_view->cameraPosition + the_view->cameraForward,
                                      the_view->cameraUp);
    auto projection_transform = glm::infinitePerspective(the_view->perspectiveFOVY,
                                                         the_view->perspectiveAspect, the_view->perspectiveNear);
    auto vp_transform = projection_transform * view_transform;


    static auto last_time = 0.0;
    auto time = glfwGetTime();
    auto delta_time = time - last_time;
    last_time = time;
    for (auto artf : artf_list) {

        // Call animation step for rotating artifacts (skip terrain)
        if (artf->theShape != terrain_shape) {
            artf->worldTransformation->animationStep(time, delta_time);
        }

        auto model_transform = artf->worldTransformation->getMatrix();
        auto transform = vp_transform * model_transform;
        shader->setMat4("u_transform", transform);

        
        glDrawArrays(GL_TRIANGLES, artf->theShape->bufferStart, artf->theShape->bufferSize);
       

    }
}


static float lr_scale = .1f;
static float fb_scale = .1f;
static float ud_scale = .1f;

static float lr_pan_scale = .01f;
static float ud_pan_scale = lr_pan_scale;




void general_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    /*
    * These variables are used to hold the window height and width and position to use when
    *  exiting full screen.
    */
    static int old_width, old_height, old_xpos, old_ypos;
    auto position0 = the_view->cameraPosition;
    if (action == GLFW_PRESS || action == GLFW_REPEAT)
    {
        switch(key) {
            case GLFW_KEY_A:
            case GLFW_KEY_LEFT:
                the_view->cameraPosition += lr_scale * the_view->cameraLeft;
                break;
            case GLFW_KEY_D:
            case GLFW_KEY_RIGHT:
                the_view->cameraPosition -= lr_scale * the_view->cameraLeft;
                break;
            case GLFW_KEY_W:
                the_view->cameraPosition += fb_scale * the_view->cameraForward;
                break;
            case GLFW_KEY_S:
                the_view->cameraPosition -= fb_scale * the_view->cameraForward;
                break;
            case GLFW_KEY_UP:
                the_view->cameraPosition += ud_scale * the_view->cameraUp;
                break;
            case GLFW_KEY_DOWN:
                the_view->cameraPosition -= ud_scale * the_view->cameraUp;
                break;
            case GLFW_KEY_ESCAPE:
                glfwSetWindowShouldClose(window, GLFW_TRUE);
                break;
            case GLFW_KEY_F11:
                // only a key press, not repeats as that could cause chaotic window/full-screen switching
                if(action == GLFW_PRESS) {
                    if (!glfwGetWindowMonitor(window)) {
                        glfwGetWindowPos(window, &old_xpos, &old_ypos);
                        glfwGetWindowSize(window, &old_width, &old_height);
                        auto monitor = glfwGetPrimaryMonitor();
                        const auto* mode = glfwGetVideoMode(monitor);
                        glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
                    }
                    else  {
                        glfwSetWindowMonitor(window, nullptr, old_xpos, old_ypos, old_width, old_height, 0);
                    }
                }
                break;
            case GLFW_KEY_Y:
                movement_restricted = !movement_restricted;
                break;
            default: ;
                // nothing to do on other keys
        }
    }

    if(movement_restricted) {
        // code restricting the movement goes in here.
        auto terrain_altitude = terrain_height_field->altitude(the_view->cameraPosition.x, the_view->cameraPosition.z);
        the_view->cameraPosition.y = terrain_altitude + 1.0f;
        
        // Check boundaries and height restrictions
        if (the_view->cameraPosition.y > max_height ||
            the_view->cameraPosition.x < 0 ||
            the_view->cameraPosition.x > terrain_scale.x + terrain_translate.x ||
            the_view->cameraPosition.z < 0 ||
            the_view->cameraPosition.z > terrain_scale.z + terrain_translate.z) {
            the_view->cameraPosition = position0;
        }
    }
#ifdef LOG_FLUP
    the_view->display_parameters();
#endif
}


void window_size_callback(GLFWwindow* window, int width, int height)
{
    auto* view = static_cast<cs4722::View*>(glfwGetWindowUserPointer(window));
    int widthfb, heightfb;
    glfwGetFramebufferSize(window, &widthfb, &heightfb);
    glViewport(0, 0, widthfb, heightfb);
    view->perspectiveAspect =
        (static_cast<float>(widthfb) / static_cast<float>(heightfb));

}



void move_callback(GLFWwindow* window, double xpos, double ypos)
{
    static auto last_x = 0.0f;
    static auto last_y = 0.0f;
    auto* view = static_cast<cs4722::View*>(glfwGetWindowUserPointer(window));
     auto dx = xpos - last_x;
     auto dy = ypos - last_y;
     last_x = xpos;
     last_y = ypos;

    // Save camera directions at the beginning (bonus feature)
    auto saved_up = view->cameraUp;
    auto saved_forward = view->cameraForward;
    auto saved_left = view->cameraLeft;    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT))
    {
        auto const rot_lr = glm::mat3(glm::rotate(glm::identity<glm::mat4>(),
            static_cast<float>(-dx * lr_pan_scale), glm::vec3(0, 1, 0)));
        view->cameraLeft = rot_lr * view->cameraLeft;
        view->cameraForward = rot_lr * view->cameraForward;
        view->cameraUp = rot_lr * view->cameraUp;

        auto const rot_ud = glm::mat3(glm::rotate(glm::identity<glm::mat4>(),
            static_cast<float>(dy * ud_pan_scale), view->cameraLeft));
        view->cameraUp = rot_ud * view->cameraUp;
        view->cameraForward = rot_ud * view->cameraForward;
        
        // Bonus feature: prevent camera from flipping over (works in both terrain and flying modes)
        // Test if the dot product of (0,1,0) and the camera's new up vector is negative
        if (glm::dot(glm::vec3(0, 1, 0), glm::vec3(view->cameraUp)) < 0) {
            // Restore saved camera directions
            view->cameraUp = saved_up;
            view->cameraForward = saved_forward;
            view->cameraLeft = saved_left;
        }
    }
    
#ifdef LOG_FLUP
    the_view->display_parameters();
#endif
}


int
main(int argc, char** argv)
{
    glfwInit();

    cs4722::setOpenglVersion(3,3);
    GLFWwindow *window = cs4722::setup_window_9_16_9("Terrain Transit");

    gladLoadGL(glfwGetProcAddress);

    init();
    the_view->perspectiveAspect = cs4722::getAspectRatio(window);

    glfwSetWindowUserPointer(window, the_view);
    glfwSetKeyCallback(window, general_key_callback);
    glfwSetCursorPosCallback(window, move_callback);
    glfwSetWindowSizeCallback(window, window_size_callback);

	
    while (!glfwWindowShouldClose(window))
    {
        glClearBufferfv(GL_COLOR, 0, cs4722::X11::gray50.asFloatArray());
        glClear(GL_DEPTH_BUFFER_BIT);
        render();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);

    glfwTerminate();
}
