#include "renderer.h"

namespace s_preview
{
    bool Renderer::gl_transparent = false;

    Renderer::Renderer(QWidget *parent) : QOpenGLWidget(parent)
    {
        is_transparent = QSurfaceFormat::defaultFormat().profile() == QSurfaceFormat::CoreProfile;

        if (gl_transparent) {
            QSurfaceFormat fmt = format();
            fmt.setAlphaBufferSize(8);
            setFormat(fmt);
        }
    }

    Renderer::~Renderer() noexcept
    {
        cleanup();
    }

    void Renderer::cleanup()
    {
        if (prog == nullptr)
            return;
        makeCurrent();
        vbo.destroy();
        delete prog;
        prog = nullptr;
        doneCurrent();
        QObject::disconnect(context(), &QOpenGLContext::aboutToBeDestroyed, this, &Renderer::cleanup);
    }

    static const char *vertexShaderSourceCore =
            "#version 150\n"
            "in vec4 vertex;\n"
            "in vec3 normal;\n"
            "out vec3 vert;\n"
            "out vec3 vertNormal;\n"
            "uniform mat4 projMatrix;\n"
            "uniform mat4 mvMatrix;\n"
            "uniform mat3 normalMatrix;\n"
            "void main() {\n"
            "   vert = vertex.xyz;\n"
            "   vertNormal = normalMatrix * normal;\n"
            "   gl_Position = projMatrix * mvMatrix * vertex;\n"
            "}\n";

    static const char *fragmentShaderSourceCore =
            "#version 150\n"
            "in highp vec3 vert;\n"
            "in highp vec3 vertNormal;\n"
            "out highp vec4 fragColor;\n"
            "uniform highp vec3 lightPos;\n"
            "void main() {\n"
            "   highp vec3 L = normalize(lightPos - vert);\n"
            "   highp float NL = max(dot(normalize(vertNormal), L), 0.0);\n"
            "   highp vec3 color = vec3(0.39, 1.0, 0.0);\n"
            "   highp vec3 col = clamp(color * 0.2 + color * 0.8 * NL, 0.0, 1.0);\n"
            "   fragColor = vec4(col, 1.0);\n"
            "}\n";

    static const char *vertexShaderSource =
            "attribute vec4 vertex;\n"
            "attribute vec3 normal;\n"
            "varying vec3 vert;\n"
            "varying vec3 vertNormal;\n"
            "uniform mat4 projMatrix;\n"
            "uniform mat4 mvMatrix;\n"
            "uniform mat3 normalMatrix;\n"
            "void main() {\n"
            "   vert = vertex.xyz;\n"
            "   vertNormal = normalMatrix * normal;\n"
            "   gl_Position = projMatrix * mvMatrix * vertex;\n"
            "}\n";

    static const char *fragmentShaderSource =
            "varying highp vec3 vert;\n"
            "varying highp vec3 vertNormal;\n"
            "uniform highp vec3 lightPos;\n"
            "void main() {\n"
            "   highp vec3 L = normalize(lightPos - vert);\n"
            "   highp float NL = max(dot(normalize(vertNormal), L), 0.0);\n"
            "   highp vec3 color = vec3(0.39, 1.0, 0.0);\n"
            "   highp vec3 col = clamp(color * 0.2 + color * 0.8 * NL, 0.0, 1.0);\n"
            "   gl_FragColor = vec4(col, 1.0);\n"
            "}\n";

    QList<GLfloat> Renderer::addQuad(QVector3D a, QVector3D b, QVector3D c)
    {
        QVector3D d = QVector3D::crossProduct(b - a, c - b) + a;
        return {a.x(), a.y(), a.z(), b.x(), b.y(), b.z(), c.x(), c.y(), c.z(),
                a.x(), a.y(), a.z(), c.x(), c.y(), c.z(), d.x(), d.y(), d.z()};
    }


    QList<GLfloat> Renderer::addCube(QVector3D origin, float width, float height)
    {
        QList<GLfloat> res;

//        res.append(addQuad(origin, QVector3D(origin.x() + width, origin.y() + height, origin.z())));
//        res.append(addQuad(QVector3D(origin.x() + width, origin.y(), origin.z()), QVector3D(origin.x() + width, origin.y() + height, origin.z() + width)));
//        res.append(addQuad(QVector3D(origin.x() + width, origin.y(), origin.z() + width), QVector3D(origin.x() + width, origin.y() + height, origin.z() + width)));
//        res.append(addQuad(QVector3D(origin.x(), origin.y(), origin.z() + width), QVector3D(origin.x(), origin.y() + height, origin.z())));
        return res;
    }

    void Renderer::initializeGL()
    {
        connect(context(), &QOpenGLContext::aboutToBeDestroyed, this, &Renderer::cleanup);

        initializeOpenGLFunctions();
        glClearColor(1.0, 1.0, 1.0, gl_transparent ? 0 : 1);

        prog = new QOpenGLShaderProgram;
        prog->addShaderFromSourceCode(QOpenGLShader::Vertex, is_transparent ? vertexShaderSourceCore : vertexShaderSource);
        prog->addShaderFromSourceCode(QOpenGLShader::Fragment, is_transparent ? fragmentShaderSourceCore : fragmentShaderSource);

        prog->bindAttributeLocation("vertex", 0);
        prog->bindAttributeLocation("normal", 1);
        prog->link();
        prog->bind();

        loc.projMatrix = prog->uniformLocation("projMatrix");
        loc.mvMatrix = prog->uniformLocation("mvMatrix");
        loc.normalMatrix = prog->uniformLocation("normalMatrix");
        loc.lightPos = prog->uniformLocation("lightPos");

        vao.create();
        QOpenGLVertexArrayObject::Binder vaoBinder(&vao);

        // TODO initialize vertex attributes

        // add a triangle
        //QList<GLfloat> data = {0.1, 0.1, 0.1, 0.3, 0.1, 0.1, 0.3, 0.3, 0.1,
        //                       0.3, 0.3, 0.1, 0.3, 0.3, 0.3, 0.3, 0.1, 0.1};

        QList<GLfloat> data = addQuad({0.1, 0.1, 0.1}, {0.3, 0.1, 0.1}, {0.3, 0.2, 0.3});
        //QList<GLfloat> data = addCube(QVector3D(0.1, 0.1, 0.1), 0.2, 0.2);
        points = data.size();
        size_t verts = data.size() / 3;

        vbo.create();
        vbo.bind();
        vbo.allocate(data.constData(), points * sizeof(GLfloat));

        // bind vbo
        vbo.bind();
        QOpenGLFunctions* f = QOpenGLContext::currentContext()->functions();
        f->glEnableVertexAttribArray(0);
        f->glEnableVertexAttribArray(1);
        f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), nullptr);
        f->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), reinterpret_cast<void*>(points * sizeof(GLfloat)));
        vbo.release();

        mat.camera.setToIdentity();
        mat.camera.translate(0, 0, -1);

        prog->setUniformValue(loc.lightPos, QVector3D(0, 0, 70));
        prog->release();
    }

    void Renderer::paintGL()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);
        //glEnable(GL_CULL_FACE); // TODO enable this on production

        mat.world.setToIdentity();
        mat.world.rotate(180.0f - ((float)rot.x / 16.0f), 1, 0, 0);
        mat.world.rotate((float)rot.y / 16.0f, 0, 1, 0);
        mat.world.rotate((float)rot.z / 16.0f, 0, 0, 1);

        QOpenGLVertexArrayObject::Binder vaoBinder(&vao);
        prog->bind();
        prog->setUniformValue(loc.projMatrix, mat.proj);
        prog->setUniformValue(loc.mvMatrix, mat.camera * mat.world);
        QMatrix3x3 normal = mat.world.normalMatrix();
        prog->setUniformValue(loc.normalMatrix, normal);

        // TODO add actual rendering
        glDrawArrays(GL_TRIANGLES, 0, points / 3);

        prog->release();
    }

    void Renderer::resizeGL(int width, int height)
    {
        mat.proj.setToIdentity();
        mat.proj.perspective(45.0f, GLfloat(width) / GLfloat(height), 0.01f, 100.0f);
    }

    void Renderer::mousePressEvent(QMouseEvent* event)
    {
        mouse_pos = event->position().toPoint();
    }

    void Renderer::mouseMoveEvent(QMouseEvent *event)
    {
        int dx = event->position().toPoint().x() - mouse_pos.x();
        int dy = event->position().toPoint().y() - mouse_pos.y();

        if (event->buttons() & Qt::LeftButton)
        {
            setRotation({rot.x + 8 * dy, Direction::X});
            setRotation({rot.y + 8 * dx, Direction::Y});
        }
        else if (event->buttons() & Qt::RightButton)
        {
            setRotation({rot.x + 8 * dy, Direction::X});
            setRotation({rot.z + 8 * dx, Direction::Z});
        }
        mouse_pos = event->position().toPoint();
    }

    static void normalize_angle(int& angle)
    {
        while (angle < 0)
            angle += 360 * 16;
        while (angle > 360 * 16)
            angle -= 360 * 16;
    }

    void Renderer::setRotation(QPair<int, Direction> angle)
    {
        normalize_angle(angle.first);
        if (angle.first != *rot.get(angle.second))
        {
            *rot.get(angle.second) = angle.first;
            update();
        }
    }

    int* Rotation::get(Direction dir) {
        switch(dir)
        {
            case Direction::X:
                return &x;
            case Direction::Y:
                return &y;
            case Direction::Z:
                return &z;
        }
    }
} // namespace s_preview