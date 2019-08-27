#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QObject>
#include <QWidget>
#include <fstream>

#include <QFileDialog>
#include <QLabel>
#include <QMenuBar>
#include <QMainWindow>
#include <CGAL/Linear_cell_complex_for_combinatorial_map.h>
#include <CGAL/draw_linear_cell_complex.h>

 #include <CGAL/Linear_cell_complex_constructors.h>

#include <iostream>

#include <fstream>

#include <CGAL/Surface_mesh_simplification/edge_collapse.h>
// Stop-condition policy

#include <CGAL/Surface_mesh_simplification/Policies/Edge_collapse/Count_stop_predicate.h>
#include <CGAL/Surface_mesh_simplification/Policies/Edge_collapse/Edge_length_cost.h>
#include <CGAL/Surface_mesh_simplification/Policies/Edge_collapse/Midpoint_placement.h>
#include <CGAL/Surface_mesh_simplification/Edge_collapse_visitor_base.h>
#include <CGAL/Surface_mesh_simplification/Policies/Edge_collapse/Edge_profile.h>


#include <CGAL/Linear_cell_complex_for_bgl_combinatorial_map_helper.h>
#include <CGAL/boost/graph/graph_traits_Linear_cell_complex_for_combinatorial_map.h>
#include <CGAL/Surface_mesh_simplification/Edge_collapse_visitor_base.h>
#include "edge_collapse_recorder.h"

#include "manipulatedframesetconstraint.h"
#include <QGLViewer/manipulatedFrame.h>

#include <QMouseEvent>

using namespace qglviewer;


typedef CGAL::Simple_cartesian<double> Kernel;
typedef CGAL::Linear_cell_complex_traits<3, Kernel> MyTraits;

typedef CGAL::Linear_cell_complex_for_bgl_combinatorial_map_helper<2, 3, MyTraits>::type LCC;

typedef Kernel::Point_3 Point_3;


class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
 QWidget* viewer ;
   QString fileName;

   LCC lcc;

   QMainWindow qWin;

 CGAL::DefaultDrawingFunctorLCC fcolor;

signals:

public slots:
 void fileOpen();
 void removeCell();
void simplify();
void OpenOFF(QString);
void SaveOFF();
void fileSave();
void preview();
void load();

protected:
// Selection functions
  virtual void drawWithNames();
  virtual void endSelection(const QPoint &);

  // Mouse events functions
  virtual void mousePressEvent(QMouseEvent *e);
  virtual void mouseMoveEvent(QMouseEvent *e);
  virtual void mouseReleaseEvent(QMouseEvent *e);

private:
  void startManipulation();
  void drawSelectionRectangle() const;
  void addIdToSelection(int id);
  void removeIdFromSelection(int id);

  // Current rectangular selection
  QRect rectangle_;

  // Different selection modes
  enum SelectionMode { NONE, ADD, REMOVE };
  SelectionMode selectionMode_;

  QList<Object *> objects_;
  QList<int> selection_;
};

#endif // MAINWINDOW_H
