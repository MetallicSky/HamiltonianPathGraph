#pragma once
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QGraphicsTextItem>
#include <QMouseEvent>
#include <QMap>
#include <QGraphicsSceneMouseEvent>

using std::vector;

class VertexItem : public QGraphicsEllipseItem {
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
public:
    explicit VertexItem(size_t id, const QPointF& pos);

    size_t id;
    QList<class EdgeItem*> edges;
    void setHighlight(bool highlight);
    void setGrayMode(bool gray);
};

class EdgeItem : public QGraphicsLineItem {
public:
    EdgeItem(VertexItem* v1, VertexItem* v2, double weight);

    // Public getter methods
    VertexItem* getVertex1() const { return v1; }
    VertexItem* getVertex2() const { return v2; }

    void setGrayMode(bool gray);
    VertexItem* otherVertex(VertexItem* v) const;

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;

private:
    VertexItem* v1;
    VertexItem* v2;
    QGraphicsTextItem* weightLabel;
};

class GraphView : public QGraphicsView {
public:
    explicit GraphView(QGraphicsScene* scene) : QGraphicsView(scene) {
        setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
        setDragMode(QGraphicsView::ScrollHandDrag);
    }

protected:
    void wheelEvent(QWheelEvent* event) override {
        qreal factor = event->angleDelta().y() > 0 ? 1.15 : 0.85;
        scale(factor, factor);
    }
};

class GraphScene : public QGraphicsScene {
    Q_OBJECT
public:
    GraphScene(QObject* parent = nullptr);
    void addVertex(size_t id, const QPointF& pos);
    void addEdge(size_t v1, size_t v2, double weight);
    void updateSelection(VertexItem* vertex);
    void selectPath(vector<size_t> path);
    void clearEdges();

private:
    VertexItem* previouslySelectedVertex = nullptr;  // Track last selected vertex
    QMap<size_t, VertexItem*> vertices;  // Map for ID lookup
    VertexItem* selectedVertex = nullptr;
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
};
