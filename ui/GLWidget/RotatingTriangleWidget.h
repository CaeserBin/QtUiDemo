#ifndef ROTATING_TRIANGLE_WIDGET_H
#define ROTATING_TRIANGLE_WIDGET_H

#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLWidget>
#include <QTime>
#include <QTimer>

class RotatingTriangleWidget final : public QOpenGLWidget,
                                     protected QOpenGLFunctions_3_3_Core {
    Q_OBJECT

public:
    explicit RotatingTriangleWidget(QWidget *parent = nullptr);
    ~RotatingTriangleWidget() override;

protected:
    // OpenGL生命周期函数
    void initializeGL() override; // 初始化OpenGL
    void paintGL() override; // 绘制场景
    void resizeGL(int w, int h) override; // 窗口大小改变

private slots:
    void updateAnimation(); // 更新动画的槽函数

private:
    QTimer *animationTimer; // 动画定时器
    QTime frameTime; // 用于计算时间
    float rotationAngle; // 当前旋转角度

    // 着色器程序相关的变量
    GLuint shaderProgram; // 着色器程序ID
    GLuint VAO; // 顶点数组对象
    GLuint VBO; // 顶点缓冲对象

    // 编译着色器的辅助函数
    GLuint compileShader(GLenum type, const char *source);
};

#endif // ROTATING_TRIANGLE_WIDGET_H
