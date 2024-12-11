#include "graphscene.h"
#include <QPen>
#include <QBrush>
#include <QFont>

VertexItem::VertexItem(int id, const QPointF& pos)
    : QGraphicsEllipseItem(-10, -10, 20, 20), id(id) {
    setPos(pos);
    setBrush(Qt::blue);
    setFlag(ItemIsSelectable, true);
}

void VertexItem::setHighlight(bool highlight) {
    if (highlight) {
        setPen(QPen(Qt::red, 3));
    }
    else {
        setPen(QPen(Qt::NoPen));
    }

}

void VertexItem::setGrayMode(bool gray) {
    setBrush(gray ? Qt::lightGray : Qt::blue);
}

EdgeItem::EdgeItem(VertexItem* v1, VertexItem* v2, double weight)
    : v1(v1), v2(v2) {
    setLine(QLineF(v1->pos(), v2->pos()));
    QFont font("Arial", 8);
    weightLabel = new QGraphicsTextItem(QString::number(weight), this);
    weightLabel->setFont(font);
    weightLabel->setPos((v1->pos() + v2->pos()) / 2);
    v1->edges.append(this);
    v2->edges.append(this);
}

void EdgeItem::setGrayMode(bool gray) {
    setPen(QPen(gray ? Qt::lightGray : Qt::black, 2));
    weightLabel->setDefaultTextColor(gray ? Qt::lightGray : Qt::black);
}

VertexItem* EdgeItem::otherVertex(VertexItem* v) const {
    return v == v1 ? v2 : v1;
}

GraphScene::GraphScene(QObject* parent) : QGraphicsScene(parent) {}

void GraphScene::addVertex(int id, const QPointF& pos) {
    auto vertex = new VertexItem(id, pos);
    addItem(vertex);
}

void GraphScene::addEdge(int v1Id, int v2Id, double weight) {
    auto v1 = static_cast<VertexItem*>(items().at(v1Id));
    auto v2 = static_cast<VertexItem*>(items().at(v2Id));
    auto edge = new EdgeItem(v1, v2, weight);
    addItem(edge);
}

void GraphScene::updateSelection(VertexItem* vertex) {
    if (selectedVertex == vertex) return;
    selectedVertex = vertex;

    for (auto item : items()) {
        if (auto v = dynamic_cast<VertexItem*>(item)) {
            v->setGrayMode(true);
        } else if (auto e = dynamic_cast<EdgeItem*>(item)) {
            e->setGrayMode(true);
        }
    }

    if (vertex) {
        vertex->setGrayMode(false);
        vertex->setHighlight(true);
        for (auto edge : vertex->edges) {
            edge->setGrayMode(false);
            edge->otherVertex(vertex)->setGrayMode(false);
        }
    }
}
