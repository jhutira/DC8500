#include <gui/sflapscreen_screen/sflapScreenView.hpp>
#include <gui/sflapscreen_screen/sflapScreenPresenter.hpp>

sflapScreenPresenter::sflapScreenPresenter(sflapScreenView& v)
    : view(v)
{

}

void sflapScreenPresenter::activate()
{
	pidConfig_st conf;

	conf = model->getFlapPidConfig(SEC_F);
	view.initPIDValues(conf);
}

void sflapScreenPresenter::deactivate()
{

}

void sflapScreenPresenter::setPIDValues(pidConfig_st conf)
{
	pidConfig_st pid_conf;

	pid_conf = model->getFlapPidConfig(SEC_F);
	pid_conf.kp = conf.kp;
	pid_conf.ki = conf.ki;
	pid_conf.kd = conf.kd;
	pid_conf.dt = conf.dt;
	pid_conf.outputMin = conf.outputMin;
	pid_conf.outputMax = conf.outputMax;
	model->setFlapPidConfig(SEC_F, pid_conf);
}
