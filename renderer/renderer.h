// https://code.qt.io/cgit/qt/qtbase.git/tree/examples/opengl/hellogl2/

#ifndef RENDERER_H
#define RENDERER_H

#include <iostream>
#include <QWidget>
#include <QWindow>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QMatrix4x4>
#include <QMouseEvent>

namespace s_preview
{
    struct Matrix_loc
    {
    public:
        int projMatrix = 0;
        int mvMatrix = 0;
        int normalMatrix = 0;
        int lightPos = 0;
    };

    struct Matrices
    {
    public:
        QMatrix4x4 proj;
        QMatrix4x4 camera;
        QMatrix4x4 world;
    };

    enum Direction
    {
        X = 0,
        Y = 1,
        Z = 2
    };

    class Rotation
    {
    public:
        int x = 0;
        int y = 0;
        int z = 0;
        int* get(Direction dir);
    };

    class Renderer : public QOpenGLWidget, protected QOpenGLFunctions
    {
        Q_OBJECT
    public:
        explicit Renderer(QWidget *parent = nullptr);

        ~Renderer() noexcept override;

    public slots:
        void cleanup();
        void setRotation(QPair<int, s_preview::Direction> angle);

    protected:
        static QList<GLfloat> addQuad(QVector3D a, QVector3D b, QVector3D c);

        static QList<GLfloat> addCube(QVector3D origin, float width, float height);

        void initializeGL() override;

        void paintGL() override;

        void resizeGL(int width, int height) override;

        void mousePressEvent(QMouseEvent *event) override;

        void mouseMoveEvent(QMouseEvent *event) override;

        static bool gl_transparent;
        bool is_transparent;

        Matrix_loc loc;
        QOpenGLShaderProgram* prog = nullptr;
        QOpenGLVertexArrayObject vao;
        QOpenGLBuffer vbo;
        // QOpenGLBuffer vbo;
        size_t points = 0;

        Matrices mat;
        QPoint mouse_pos;
        Rotation rot;
    };

} // namespace s_preview

#endif //RENDERER_H
