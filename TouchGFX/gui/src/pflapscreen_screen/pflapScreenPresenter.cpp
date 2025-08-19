#include <gui/pflapscreen_screen/pflapScreenView.hpp>
#include <gui/pflapscreen_screen/pflapScreenPresenter.hpp>

pflapScreenPresenter::pflapScreenPresenter(pflapScreenView& v)
    : view(v)
{

}

void pflapScreenPresenter::activate()
{
	pidConfig_st conf;

	conf = model->getFlapPidConfig(PRIM_F);
	view.initPIDValues(conf);
}

void pflapScreenPresenter::deactivate()
{

}

void pflapScreenPresenter::setPIDValues(pidConfig_st conf)
{
	pidConfig_st pid_conf;

	pid_conf = model->getFlapPidConfig(PRIM_F);
	pid_conf.kp = conf.kp;
	pid_conf.ki = conf.ki;
	pid_conf.kd = conf.kd;
	pid_conf.dt = conf.dt;
	pid_conf.outputMin = conf.outputMin;
	pid_conf.outputMax = conf.outputMax;
	model->setFlapPidConfig(PRIM_F, pid_conf);
}
