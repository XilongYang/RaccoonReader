#include "toc.h"
#include <QTreeWidgetItem>
#include <QDebug>
#include <QHeaderView>

namespace  {
    QString ExtractPageNum(const QString& str) {
        auto list = str.split(";");
        return list.at(1);
    }
}

Toc::Toc(Document* doc, QWidget* parent) {
    this->setParent(parent);
    SetDocument(doc);
    QStringList headers;
    headers << "Name" << "Page";
    this->setHeaderLabels(headers);
    this->setHeaderHidden(true);
    this->setColumnHidden(1, true);
}

void Toc::SetDocument(Document* doc) {
    this->clear();
    if (doc == nullptr) return;
    outlineItem_ = doc->outline();
    for (int i = 0; i < outlineItem_.size(); ++i) {
        auto curItem = outlineItem_.at(i);
        auto tmp = new QTreeWidgetItem(this);
        tmp->setText(0, curItem.name());
        auto pageData = curItem.destination().data();
        if(pageData != nullptr) {
            auto pageNum = ExtractPageNum(pageData->toString());
            tmp->setText(1, pageNum);
        }
        if (curItem.hasChildren()) {
            GenerateSubItem(tmp, curItem.children());
        }
    }
}

void Toc::HighLightItem(int n) {
    QTreeWidgetItemIterator it(this);
    while (*it) {
        if((*it)->text(1).toInt() > n) {
            --it;
            break;
        }
        ++it;
    }
    this->setCurrentItem(*it);
}

void Toc::GenerateSubItem(QTreeWidgetItem* parent, const QVector<OutlineItem>& outlines) {
    for(int i = 0; i < outlines.size(); ++i) {
        auto curItem = outlines.at(i);
        auto tmp = new QTreeWidgetItem(parent);
        tmp->setText(0, curItem.name());
        auto pageData = curItem.destination().data();
        if(pageData != nullptr) {
            auto pageNum = ExtractPageNum(pageData->toString());
            tmp->setText(1, pageNum);
        }
        if(curItem.hasChildren()) {
            GenerateSubItem(tmp, curItem.children());
        }
    }
}