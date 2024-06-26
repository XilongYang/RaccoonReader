/*
**  This file is part of Raccoon Reader.
**
** 	mainwindow.h: Declaration of MainWindow class.
**
**  Copyright 2021 Yang XiLong
*/

#ifndef PDFVIEW_H
#define PDFVIEW_H

#include <QObject>
#include <QGraphicsView>
#include <QMap>
#include <functional>

#include <poppler/qt5/poppler-qt5.h>

using Poppler::Document;
using std::function;

class PdfState;

class PdfView : public QGraphicsView
{
    Q_OBJECT
public:
    enum FitMode {
        None, FitWidth, FitHeight, FitPage
    };
    PdfView(QWidget* parent = nullptr);
    PdfView(const QString& path, QWidget* parent = nullptr);
    PdfView(const PdfView&) = delete;
    PdfView(PdfView&&) = delete;
    PdfView& operator=(const PdfView&) = delete;
    PdfView& operator=(PdfView&&) = delete;
    ~PdfView();
    int pageNum() const;
    int pageCount() const;
    double zoomLevel() const;
    Document* document() const;
    void setPageNum(int n);
    void setDocument(Document* doc);
    void setZoomLevel(double zoomLevel);
    FitMode fitMode();
    void setFitMode(FitMode fitMode);
    void clearFitMode();
protected:
    void mousePressEvent(QMouseEvent *e) override;
    void mouseMoveEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
    void wheelEvent(QWheelEvent *e) override;
    void keyPressEvent(QKeyEvent *e) override;
    void keyReleaseEvent(QKeyEvent *e) override;
    void resizeEvent(QResizeEvent *e) override;
    void focusOutEvent(QFocusEvent *e) override;
private:
    PdfState *state_;
    int pageNum_ = 0;
    double zoomLevel_ = 1;
    FitMode fitMode_;
    Document* doc_;

    void changeState();
signals:
    void pageChanged(int n);
    void scaleChanged(double scale);
    void fitModeChanged(FitMode fitmode);
};

#endif // PDFVIEW_H
