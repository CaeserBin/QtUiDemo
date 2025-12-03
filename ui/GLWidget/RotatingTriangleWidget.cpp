#include "RotatingTriangleWidget.h"
#include <QDebug>
#include <cmath>

// 顶点着色器源码 - 非常简单的版本
const char *vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
uniform float uRotation;  // 旋转角度
out vec3 ourColor;
void main()
{
    // 创建旋转矩阵（绕Z轴旋转）
    float c = cos(uRotation);
    float s = sin(uRotation);
    mat3 rotation = mat3(
        c, -s, 0.0,
        s,  c, 0.0,
        0.0, 0.0, 1.0
    );
    // 应用旋转
    vec3 rotatedPos = rotation * aPos;
    gl_Position = vec4(rotatedPos, 1.0);
    ourColor = aColor;
}
)";

// 片段着色器源码
const char *fragmentShaderSource = R"(
#version 330 core
in vec3 ourColor;
out vec4 FragColor;

void main()
{
    FragColor = vec4(ourColor, 1.0);
}
)";

RotatingTriangleWidget::RotatingTriangleWidget(QWidget *parent) :
    QOpenGLWidget(parent), rotationAngle(0.0f) {
    // 创建定时器用于动画
    animationTimer = new QTimer(this);
    connect(animationTimer, &QTimer::timeout, this,
            &RotatingTriangleWidget::updateAnimation);

    // 设置更新频率：每秒60帧
    animationTimer->start(16); // 约60 FPS

    // 开始计时
    frameTime.start();
}

RotatingTriangleWidget::~RotatingTriangleWidget() {
    // 清理OpenGL资源
    makeCurrent();
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
    doneCurrent();

    delete animationTimer;
}

void RotatingTriangleWidget::initializeGL() {
    // 初始化OpenGL函数
    initializeOpenGLFunctions();

    // 设置清屏颜色为深灰色
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    // 编译和链接着色器
    const GLuint vertexShader =
            compileShader(GL_VERTEX_SHADER, vertexShaderSource);
    const GLuint fragmentShader =
            compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    // 创建着色器程序
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // 检查链接错误
    GLint success;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        qDebug() << "着色器程序链接失败：" << infoLog;
    }

    // 删除着色器对象（已链接到程序）
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // 三角形的顶点数据（位置 + 颜色）
    constexpr float vertices[] = {
            // 位置              // 颜色
            0.0f,  0.5f,  0.0f, 1.0f, 0.0f, 0.0f, // 顶点1：红色
            -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // 顶点2：绿色
            0.5f,  -0.5f, 0.0f, 0.0f, 0.0f, 1.0f // 顶点3：蓝色
    };

    // 创建顶点数组对象(VAO)和顶点缓冲对象(VBO)
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // 绑定VAO（后续操作会记录在VAO中）
    glBindVertexArray(VAO);

    // 绑定VBO并复制顶点数据
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // 设置顶点属性指针
    // 位置属性
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                          (void *) 0);
    glEnableVertexAttribArray(0);

    // 颜色属性
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                          (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // 解绑VBO和VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    qDebug() << "OpenGL初始化完成！";
}

void RotatingTriangleWidget::paintGL() {
    // 清除颜色缓冲区
    glClear(GL_COLOR_BUFFER_BIT);

    // 使用我们的着色器程序
    glUseProgram(shaderProgram);

    // 设置旋转角度uniform
    GLint rotationLoc = glGetUniformLocation(shaderProgram, "uRotation");
    glUniform1f(rotationLoc, rotationAngle);

    // 绘制三角形
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    // 解绑
    glBindVertexArray(0);
}

void RotatingTriangleWidget::resizeGL(const int w, const int h) {
    // 设置视口为整个窗口大小
    glViewport(0, 0, w, h);
}

void RotatingTriangleWidget::updateAnimation() {
    // 计算时间增量（使动画速度与帧率无关）
    static float lastTime = 0;
    const float currentTime = frameTime.elapsed() / 1000.0f; // 转换为秒
    const float deltaTime = currentTime - lastTime;
    lastTime = currentTime;

    // 更新旋转角度（每秒旋转90度）
    rotationAngle += deltaTime * 1.5f; // 约90度/秒

    // 保持角度在0-2π范围内
    if (rotationAngle > 6.283185f) // 2π ≈ 6.283
        rotationAngle -= 6.283185f;

    // 请求重绘（这会触发paintGL()的调用）
    update();
}

// 编译着色器的辅助函数
GLuint RotatingTriangleWidget::compileShader(const GLenum type,
                                             const char *source) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    // 检查编译错误
    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        qDebug() << (type == GL_VERTEX_SHADER ? "顶点" : "片段")
                 << "着色器编译失败：" << infoLog;
        return 0;
    }

    return shader;
}
