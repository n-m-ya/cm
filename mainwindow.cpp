#include "mainwindow.h"
#include <QString>
#include <QInputDialog>
 #include <time.h>

namespace SMS = CGAL::Surface_mesh_simplification ;
typedef boost::graph_traits<LCC>::vertex_descriptor vertex_descriptor;
typedef boost::graph_traits<LCC>::edge_descriptor edge_descriptor;
typedef boost::graph_traits<LCC>::halfedge_descriptor halfedge_descriptor ;

typedef SMS::Edge_profile<LCC> Profile ;


struct State {
  Point_3 p;
};

struct My_visitor : public SMS::Edge_collapse_visitor_base<LCC>
{
  State& state;
  LCC& sm;

  My_visitor(State& state, LCC& sm)
    : state(state), sm(sm)
  {}

  void OnCollapsing(Profile const& profile ,boost::optional<Point> placement)
  {
    std::cout << "My_visitor::OnCollapsing()" << std::endl;
//    std::cout << profile.v0() << " will collapse into "<< profile.v1() << std::endl;
  }

  // Called AFTER each edge has been collapsed
  void OnCollapsed( Profile const&, vertex_descriptor )
  {}

  void OnSplitting(vertex_descriptor v, vertex_descriptor vL, vertex_descriptor vR)
  {
   // std::cout << "before split of vertex " << v << std::endl;
   // state.p = sm.point(v);
  }

  void OnSplit(halfedge_descriptor hd)
  {
  //  std::cout << target(hd, sm) << " at " << state.p << " was split into "
   //           << hd << " at " <<  sm.point(source(hd,sm)) << " -> " << sm.point(target(hd,sm)) << std::endl;
  }
};


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    viewer = new QWidget(this);
   setCentralWidget(viewer);

   QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
   fileMenu->addAction(QIcon("icons/open.xpm"),"Open", this, SLOT(fileOpen()));
   fileMenu->addAction(QIcon("icons/save.xpm"),"simplify", this, SLOT(simplify()));
   fileMenu->addAction(QIcon("icons/exit.xpm"),"save", this, SLOT(fileSave()));

   QMenu *viewMenu = menuBar()->addMenu(tr("&Edit"));
   viewMenu->addAction(QIcon("icons/open.xpm"),"Open", this, SLOT(fileOpen()));
   viewMenu->addAction(QIcon("icons/save.xpm"),"Save", this, SLOT(fileOpen()));
   viewMenu->addAction(QIcon("icons/exit.xpm"),"Close", this, SLOT(fileOpen()));
}


void MainWindow::SaveOFF()
{
CGAL::write_off(lcc,"temp.off" );

}

void MainWindow::preview()
{
  QWidget* centralWidget = new QWidget(viewer);

          centralWidget->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Maximum);

          setCentralWidget( new CGAL::SimpleLCCViewerQt<LCC, CGAL::DefaultDrawingFunctorLCC >(&qWin ,
                                 &lcc,
                                 "Basic LCC Viewer",
                                 false,
                                  fcolor ) );
    show();
}


void MainWindow::fileOpen()
{
     fileName = QFileDialog::getOpenFileName(this,tr("Select object"), ".", tr("*.off"));
 OpenOFF(fileName);
}



void MainWindow ::simplify()
{
clock_t tStart = clock();
    SMS::Edge_collapse_recorder <LCC,My_visitor> recorder(lcc);
    State state;
   My_visitor mvis(state, lcc);

  bool ok;
 int n = QInputDialog::getInt(this, "", tr("Number of vertices in each cell:"),lcc.number_of_darts(),0, lcc.number_of_darts(),1, &ok);

// if (ok){
//    n=lcc.number_of_halfedges()/2 - 1;
//   }

 SMS::Count_stop_predicate<LCC> stop(1000);

 int r = SMS::edge_collapse
   (lcc
    ,stop
    ,CGAL::parameters::halfedge_index_map(get(CGAL::halfedge_index, lcc))
             .vertex_index_map(get(boost::vertex_index, lcc))
             .get_cost(SMS::Edge_length_cost<LCC>())
   .get_placement(SMS::Midpoint_placement<LCC>()).visitor(recorder.visitor(mvis)));

 // std::cout << "\nEdges collapsed: "  << state.p< std::endl;

    std::cout << "\nFinished...\n" << r << " edges removed.\n"
               << (lcc.number_of_darts()/2) << " final edges.\n" ;

     lcc.display_characteristics(std::cout)<<", is_valid="<<CGAL::is_valid(lcc)<<std::endl;

    SaveOFF();
     recorder.undo(mvis);
     std::cout<<"re insert "<<std::endl;
     lcc.display_characteristics(std::cout)<<", is_valid="<<CGAL::is_valid(lcc)<<std::endl;
    std::cout<<"Time taken: %.2fs\n"<< (double)(clock() - tStart)/CLOCKS_PER_SEC<< std::endl;

   // OpenOFF("temp.off");

 }

 void MainWindow ::removeCell()
 {
//     dh1= lcc.darts().begin() ;

//     if( (lcc.is_removable<1>(dh1)) ){
//    lcc.remove_cell<1>(dh1);
//     }

     lcc.display_characteristics(std::cout) << ", valid="
                      << lcc.is_valid() << std::endl;
  }
 void MainWindow::fileSave(){
     QString fileName = QFileDialog::getSaveFileName(this,tr("Select object"), ".", tr("*.off"));
     if(fileName != ""){
//        SaveOFF(fileName);
         std::cout<<"File saved"<<std::endl;
     }
 }

 void MainWindow::OpenOFF(QString fileName)
 {
     std::ifstream ifile(fileName.toStdString().c_str());
     if (ifile)
     {
        CGAL::read_off( ifile,lcc);
        lcc.display_characteristics(std::cout)<<", is_valid="<<CGAL::is_valid(lcc)<<std::endl;

     }
     preview();
 }

 void MainWindow::load()
 {



 }
 //   C u s t o m i z e d   m o u s e   e v e n t s

 void MainWindow::mousePressEvent(QMouseEvent *e) {
   // Start selection. Mode is ADD with Shift key and TOGGLE with Alt key.
   rectangle_ = QRect(e->pos(), e->pos());

   if ((e->button() == Qt::LeftButton) && (e->modifiers() == Qt::ShiftModifier))
     selectionMode_ = ADD;
   else if ((e->button() == Qt::LeftButton) &&
            (e->modifiers() == Qt::AltModifier))
     selectionMode_ = REMOVE;
   else {
     if (e->modifiers() == Qt::ControlModifier)
       startManipulation();
     QGLViewer::mousePressEvent(e);
   }
 }

 void MainWindow::mouseMoveEvent(QMouseEvent *e) {
   if (selectionMode_ != NONE) {
     // Updates rectangle_ coordinates and redraws rectangle
     rectangle_.setBottomRight(e->pos());
     update();
   } else
     QGLViewer::mouseMoveEvent(e);
 }

 void MainWindow::mouseReleaseEvent(QMouseEvent *e) {
   if (selectionMode_ != NONE) {
     // Actual selection on the rectangular area.
     // Possibly swap left/right and top/bottom to make rectangle_ valid.
     rectangle_ = rectangle_.normalized();
     // Define selection window dimensions
     setSelectRegionWidth(rectangle_.width());
     setSelectRegionHeight(rectangle_.height());
     // Compute rectangle center and perform selection
     select(rectangle_.center());
     // Update display to show new selected objects
     update();
   } else
     QGLViewer::mouseReleaseEvent(e);
 }

 //   C u s t o m i z e d   s e l e c t i o n   p r o c e s s

 void MainWindow::drawWithNames() {
   for (int i = 0; i < int(objects_.size()); i++) {
     glPushName(i);
     objects_.at(i)->draw();
     glPopName();
   }
 }

 void MainWindow::endSelection(const QPoint &) {
   // Flush GL buffers
   glFlush();

   // Get the number of objects that were seen through the pick matrix frustum.
   // Reset GL_RENDER mode.
   GLint nbHits = glRenderMode(GL_RENDER);

   if (nbHits > 0) {
     // Interpret results : each object created 4 values in the selectBuffer().
     // (selectBuffer())[4*i+3] is the id pushed on the stack.
     for (int i = 0; i < nbHits; ++i)
       switch (selectionMode_) {
       case ADD:
         addIdToSelection((selectBuffer())[4 * i + 3]);
         break;
       case REMOVE:
         removeIdFromSelection((selectBuffer())[4 * i + 3]);
         break;
       default:
         break;
       }
   }
   selectionMode_ = NONE;
 }

 void MainWindow::startManipulation() {
   Vec averagePosition;
   ManipulatedFrameSetConstraint *mfsc =
       (ManipulatedFrameSetConstraint *)(manipulatedFrame()->constraint());
   mfsc->clearSet();

   for (QList<int>::const_iterator it = selection_.begin(),
                                   end = selection_.end();
        it != end; ++it) {
     mfsc->addObjectToSet(objects_[*it]);
     averagePosition += objects_[*it]->frame.position();
   }

   if (selection_.size() > 0)
     manipulatedFrame()->setPosition(averagePosition / selection_.size());
 }

 //   S e l e c t i o n   t o o l s

 void MainWindow::addIdToSelection(int id) {
   if (!selection_.contains(id))
     selection_.push_back(id);
 }

 void MainWindow::removeIdFromSelection(int id) { selection_.removeAll(id); }

 void MainWindow::drawSelectionRectangle() const {
   startScreenCoordinatesSystem();
   glDisable(GL_LIGHTING);
   glEnable(GL_BLEND);

   glColor4f(0.0, 0.0, 0.3f, 0.3f);
   glBegin(GL_QUADS);
   glVertex2i(rectangle_.left(), rectangle_.top());
   glVertex2i(rectangle_.right(), rectangle_.top());
   glVertex2i(rectangle_.right(), rectangle_.bottom());
   glVertex2i(rectangle_.left(), rectangle_.bottom());
   glEnd();

   glLineWidth(2.0);
   glColor4f(0.4f, 0.4f, 0.5f, 0.5f);
   glBegin(GL_LINE_LOOP);
   glVertex2i(rectangle_.left(), rectangle_.top());
   glVertex2i(rectangle_.right(), rectangle_.top());
   glVertex2i(rectangle_.right(), rectangle_.bottom());
   glVertex2i(rectangle_.left(), rectangle_.bottom());
   glEnd();

   glDisable(GL_BLEND);
   glEnable(GL_LIGHTING);
   stopScreenCoordinatesSystem();
 }
