#pragma once
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QGraphicsTextItem>
#include <QMouseEvent>
#include <QMap>
#include <QGraphicsSceneMouseEvent>

class VertexItem : public QGraphicsEllipseItem {
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
public:
    explicit VertexItem(int id, const QPointF& pos);

    int id;
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

private:
    VertexItem* v1;
    VertexItem* v2;
    QGraphicsTextItem* weightLabel;
};

class GraphScene : public QGraphicsScene {
    Q_OBJECT
public:
    GraphScene(QObject* parent = nullptr);
    void addVertex(int id, const QPointF& pos);
    void addEdge(int v1, int v2, double weight);
    void updateSelection(VertexItem* vertex);

private:
    VertexItem* previouslySelectedVertex = nullptr;  // Track last selected vertex
    QMap<int, VertexItem*> vertices;  // Map for ID lookup
    VertexItem* selectedVertex = nullptr;
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
};
