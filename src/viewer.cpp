

#include <ecto/ecto.hpp>
#include <ecto_pcl/ecto_pcl.hpp>
#include <thread>
#include <QApplication>
#include <QDesktopWidget>
#include <QSurfaceFormat>
#include "rgbd_viewer/mainwindow.h"

typedef ecto::pcl::PointCloud PointCloud;

namespace rgbd_viewer
{
  class Viewer {
    public:
      Viewer(const std::string window_name) :  name_(window_name)
      {
        thread_.reset(new std::thread(&Viewer::run, this));
      }
      ~Viewer()
      {
        stop();
        thread_->join();
        thread_.reset();
      }

      void run() {
        std::cout << "Here" << std::endl;

        char  arg0[] = "Viewer";
        char* argv[] = { &arg0[0], NULL };
        int   argc   = (int)(sizeof(argv) / sizeof(argv[0])) - 1;

        app_.reset(new QApplication(argc, argv));
        QSurfaceFormat fmt;
        fmt.setDepthBufferSize(24);
        if (QCoreApplication::arguments().contains(QStringLiteral("--multisample")))
          fmt.setSamples(4);
        if (QCoreApplication::arguments().contains(QStringLiteral("--coreprofile"))) {
          fmt.setVersion(3, 2);
          fmt.setProfile(QSurfaceFormat::CoreProfile);
        }

        QSurfaceFormat::setDefaultFormat(fmt);
        MainWindow mainWindow;
        if (QCoreApplication::arguments().contains(QStringLiteral("--transparent"))) {
            mainWindow.setAttribute(Qt::WA_TranslucentBackground);
            mainWindow.setAttribute(Qt::WA_NoSystemBackground, false);
        }
        mainWindow.resize(mainWindow.sizeHint());
        int desktopArea = QApplication::desktop()->width() *
                         QApplication::desktop()->height();
        int widgetArea = mainWindow.width() * mainWindow.height();
        if (((float)widgetArea / (float)desktopArea) < 0.75f)
            mainWindow.show();
        else
            mainWindow.showMaximized();
        app_->exec();
      }

      void stop() {
        app_->quit();
      }

    private:
      std::string name_;
      std::shared_ptr<std::thread> thread_;
      std::shared_ptr<QApplication> app_;
  };

  struct CloudViewer
  {
	  static void declare_io(const ecto::tendrils& params, ecto::tendrils& inputs, ecto::tendrils& outputs)
	  {
		inputs.declare<PointCloud> ("input", "An XYZ/XYZRGB point cloud");
	  }

	  static void
	  declare_params(ecto::tendrils& params)
	  {
		params.declare<std::string>("window_name", "The window name", "cloud viewer");
	  }

	  void
	  configure(const ecto::tendrils& params, const ecto::tendrils& inputs, const ecto::tendrils& outputs)
	  {
		std::string window_name;
		params["window_name"] >> window_name;
		impl_.reset(new Viewer(window_name));
		pc_ = inputs["input"];
	  }

      int process(const ecto::tendrils& inputs, const ecto::tendrils& outputs)
	  {
//		impl_->setPointCloud(c);
		return ecto::OK;
	  }

	  ~CloudViewer()
	  {
        if(impl_)
	      impl_->stop();
          impl_.reset();
	  }

      boost::scoped_ptr<Viewer> impl_;
      ecto::spore<PointCloud> pc_;
  };
}

ECTO_THREAD_UNSAFE(rgbd_viewer::CloudViewer);
ECTO_CELL(rgbd_viewer, rgbd_viewer::CloudViewer, "CloudViewer", "Cloud Visualizer");
