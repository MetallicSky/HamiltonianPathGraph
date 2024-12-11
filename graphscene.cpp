#include "graphscene.h"
#include <QPen>
#include <QBrush>
#include <QFont>

void VertexItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (auto scene = dynamic_cast<GraphScene*>(this->scene())) {
        scene->updateSelection(this);  // Notify the scene about the selection
    }
    QGraphicsEllipseItem::mousePressEvent(event);  // Propagate the event
}

VertexItem::VertexItem(size_t id, const QPointF& pos)
    : QGraphicsEllipseItem(-10, -10, 20, 20), id(id) {
    setPos(pos);
    setBrush(Qt::yellow);  // Default color
    setPen(QPen(Qt::black, 1));  // Default border
    setFlag(QGraphicsItem::ItemIgnoresTransformations); // Ignore view scaling

    setFlag(ItemIsSelectable, false);  // Disable default selection behavior

    // Add the index number as a label
    QGraphicsSimpleTextItem* label = new QGraphicsSimpleTextItem(QString::number(id), this);
    label->setBrush(Qt::red);
    label->setPos(-5, -7);  // Center the text
}

void VertexItem::setHighlight(bool highlight) {
    if (highlight) {
        setPen(QPen(Qt::red, 3));  // Highlight with a thicker red border
    } else {
        setPen(QPen(Qt::black, 1));  // Reset to the default black border
    }
}

void VertexItem::setGrayMode(bool gray) {
    setBrush(gray ? Qt::lightGray : Qt::yellow);
}


EdgeItem::EdgeItem(VertexItem* v1, VertexItem* v2, double weight)
    : v1(v1), v2(v2) {
    QPen pen = this->pen();
    pen.setWidthF(1);
    setPen(pen);
    setLine(QLineF(v1->pos(), v2->pos()));
    QFont font("Arial", 8);
    weightLabel = new QGraphicsTextItem(QString::number(weight), this);
    weightLabel->setFlag(QGraphicsItem::ItemIgnoresTransformations);
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

void EdgeItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen pen = this->pen();
    pen.setWidthF(1.0 / painter->transform().m11()); // Adjust width to stay consistent
    painter->setPen(pen);
    painter->drawLine(line());
}

GraphScene::GraphScene(QObject* parent) : QGraphicsScene(parent) {}

void GraphScene::addVertex(size_t id, const QPointF& pos) {
    auto vertex = new VertexItem(id, pos);
    vertex->setZValue(1);  // Ensure nodes are on top
    addItem(vertex);
    vertices[id] = vertex;
}

void GraphScene::addEdge(size_t v1Id, size_t v2Id, double weight) {
    auto v1 = vertices.value(v1Id, nullptr);
    auto v2 = vertices.value(v2Id, nullptr);

    auto edge = new EdgeItem(v1, v2, weight);
    edge->setZValue(0);  // Ensure edges are below nodes
    addItem(edge);
}

void GraphScene::updateSelection(VertexItem* vertex) {
    if (selectedVertex == vertex) return;  // No change in selection

    // Clear the previous selection
    for (auto item : items()) {
        if (auto v = dynamic_cast<VertexItem*>(item)) {
            v->setHighlight(false);       // Reset highlight for all vertices
            v->setGrayMode(true);         // Gray out all vertices initially
        }
        if (auto e = dynamic_cast<EdgeItem*>(item)) {
            e->setGrayMode(true);         // Gray out all edges initially
        }
    }

    // Update the selection
    selectedVertex = vertex;
    if (selectedVertex) {
        selectedVertex->setHighlight(true);  // Highlight the selected vertex
        selectedVertex->setGrayMode(false);  // Keep selected vertex visible

        // Highlight connected edges and neighbor vertices
        for (auto edge : selectedVertex->edges) {
            edge->setGrayMode(false);        // Keep connected edges visible
            auto neighbor = (edge->getVertex1() == selectedVertex) ? edge->getVertex2() : edge->getVertex1();
            neighbor->setGrayMode(false);   // Keep neighbor vertices visible
        }
    }
}

// Override mousePressEvent to handle selection
void GraphScene::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    // Check if the clicked item is a vertex
    if (auto vertex = dynamic_cast<VertexItem*>(itemAt(event->scenePos(), QTransform()))) {
        updateSelection(vertex);
    } else {
        updateSelection(nullptr);  // Clear selection if clicking outside any vertex
    }

    QGraphicsScene::mousePressEvent(event);  // Propagate the event
}
