#include "af903x.h"
#include "dvb_frontend.h"

struct af903xm_state {
	struct dvb_frontend demod;
	fe_bandwidth_t current_bandwidth;
};

static int af903x_init(struct dvb_frontend *demod)
{
	DWORD error = Error_NO_ERROR;
	deb_data("- Enter %s Function - chip=%d\n",__FUNCTION__, demod->dvb->num);

/*	error = DL_ApCtrl(demod->dvb->num,1 );
	if(error){
		printk("af903x_init return error\n");
		return error;
	}
*/	
	return 0;
}

static int af903x_sleep(struct dvb_frontend *demod)
{
	DWORD error = Error_NO_ERROR;;
        deb_data("- Enter %s Function - chip=%d\n",__FUNCTION__, demod->dvb->num);

	DeviceReboot = false;

 /*       error = DL_ApCtrl(demod->dvb->num, 0);
        if (error){
		 printk("af903x_sleep return error\n");
                return error;
        }
*/        
    return 0;
	
}

static int af903x_identify(struct af903xm_state *state)
{
	return 0;
}

static int af903x_get_frontend(struct dvb_frontend* fe,
				struct dvb_frontend_parameters *fep)
{
	struct af903xm_state *state = fe->demodulator_priv;
	deb_data("- Enter %s Function - chip=%d\n",__FUNCTION__, fe->dvb->num);
	fep->inversion = INVERSION_AUTO;
	fep->u.ofdm.bandwidth = state->current_bandwidth;
	return 0;
}

static int af903x_set_frontend(struct dvb_frontend* fe,
				struct dvb_frontend_parameters *fep)
{
	struct af903xm_state *state = fe->demodulator_priv;
	struct af903x_ofdm_channel ch;
	DWORD error = Error_NO_ERROR;

	deb_data("- Enter %s Function - chip=%d\n",__FUNCTION__, fe->dvb->num);
	if (fep->u.ofdm.bandwidth == 0) fep->u.ofdm.bandwidth=8;
	if (fep->u.ofdm.bandwidth == 1) fep->u.ofdm.bandwidth=7;
	if (fep->u.ofdm.bandwidth == 2) fep->u.ofdm.bandwidth=6;

	ch.RF_kHz           = fep->frequency / 1000;
	ch.Bw               = fep->u.ofdm.bandwidth;

	state->current_bandwidth = fep->u.ofdm.bandwidth;

	deb_data("- Enter %s Function - chip=%d RF=%d, BW=%d\n",__FUNCTION__, fe->dvb->num,ch.RF_kHz,ch.Bw);

	if (ch.RF_kHz<177000 || ch.RF_kHz > 8585000)
	    ch.RF_kHz = 950000;
	    
	error = DL_Tuner_SetFreqBw(fe->dvb->num,ch.RF_kHz,ch.Bw);
	if (error) printk("af903x_set_frontend  return error\n");

	return 0;
}

static int af903x_read_status(struct dvb_frontend *fe, fe_status_t *stat)
{
	//deb_data("- Enter %s Function -chip=%d\n",__FUNCTION__, fe->dvb->num);
	struct af903xm_state *state = fe->demodulator_priv;

	DWORD error = Error_NO_ERROR;
	Bool bLock;

	*stat = 0;

	error = DL_isLocked(fe->dvb->num, &bLock);
	if(error) return 0;//return error;

	if (bLock)
	{
		// It's seems ok that always return lock to AP
		*stat |= FE_HAS_SIGNAL;
		*stat |= FE_HAS_CARRIER;
		*stat |= FE_HAS_LOCK;
		*stat |= FE_HAS_VITERBI;
		*stat |= FE_HAS_SYNC;
	}

	return 0;
}

static int af903x_read_ber(struct dvb_frontend *fe, u32 *ber)
{
    struct af903xm_state *state = fe->demodulator_priv;

    DWORD error = Error_NO_ERROR;

    ChannelStatistic  channelStatistic;

    error = DL_getChannelStatistic(fe->dvb->num, &channelStatistic);
    if(error) return error;

    deb_data("- af903x_read_ber postVitErrorCount : %d, postVitBitCount :%d -\n",channelStatistic.postVitErrorCount, channelStatistic.postVitBitCount);

    *ber =  channelStatistic.postVitErrorCount * (0xFFFFFFFF /  channelStatistic.postVitBitCount);
    return 0;
}

static int af903x_read_snr(struct dvb_frontend* fe, u16 *snr)
{
//	(void) fe;
//        *snr = 0x0000;
    struct af903xm_state *state = fe->demodulator_priv;

    DWORD error = Error_NO_ERROR;
    Constellation   constellation;
    BYTE  SignalSnr = 0;

    error = DL_getSNR(fe->dvb->num, &constellation, &SignalSnr);
    if(error) return error;

    deb_data("- af903x_read_snr constellation : %d, SignalSnr :%d -\n",constellation,SignalSnr );

#ifdef QuantaMID
    *snr = (u16)SignalSnr;
#else
    if(constellation == 0)
	*snr = (u16)SignalSnr * (0xFFFF / 23) ;
    else if(constellation == 1)
	*snr = (u16)SignalSnr * (0xFFFF / 26) ;
    else if(constellation == 2)
	*snr = (u16)SignalSnr * (0xFFFF / 29) ;
    else
	deb_data("      Get constellation is failed!\n");
#endif
    return 0;
}

static int af903x_read_unc_blocks(struct dvb_frontend *fe, u32 *unc)
{
	(void) fe;
        *unc = 0;
        return 0;

}
static int af903x_read_signal_strength(struct dvb_frontend *fe, u16 *strength)
{
	struct af903xm_state *state = fe->demodulator_priv;

        DWORD error = Error_NO_ERROR;
	BYTE  SignalStrength = 0;
	Long  SignalStrengthdbm;

	deb_data("- Enter %s Function -\n",__FUNCTION__);
#ifdef QuantaMID 
	error = DL_getSignalStrengthDbm(fe->dvb->num, &SignalStrengthdbm);
	if(error) return error;

	deb_data("- af903x_read_signal_strengthDbm is -%d -\n",-SignalStrengthdbm);
	*strength = (u16)(-SignalStrengthdbm);
#else
	error = DL_getSignalStrength(fe->dvb->num, &SignalStrength);
        if(error) return error;

	deb_data("- af903x_read_signal_strength is %d -\n",SignalStrength);
	*strength = (u16)SignalStrength* (0xFFFF/100);
#endif
	return 0;
}

static void af903x_release(struct dvb_frontend *demod)
{
	struct af903xm_state *st = demod->demodulator_priv;
	deb_data("- Enter %s Function -\n",__FUNCTION__);
	kfree(st);
}

static struct dvb_frontend_ops af903x_ops;
struct dvb_frontend * af903x_attach(u8 tmp)
{
	struct dvb_frontend *demod;
	struct af903xm_state *st;

	deb_data("- Enter %s Function -\n",__FUNCTION__);	
	st = kzalloc(sizeof(struct af903xm_state), GFP_KERNEL);
	if (st == NULL)
		return NULL;

	demod                   = &st->demod;
	demod->demodulator_priv = st;
	memcpy(&st->demod.ops, &af903x_ops, sizeof(struct dvb_frontend_ops));

	af903x_identify(st); 

	return demod;
}
EXPORT_SYMBOL(af903x_attach);

static struct dvb_frontend_ops af903x_ops = {
	.info = {
		.name = "AF903X USB DVB-T",
		.type = FE_OFDM,
		.frequency_min      = 44250000,
		.frequency_max      = 867250000,
		.frequency_stepsize = 62500,
		.caps = FE_CAN_INVERSION_AUTO |
			FE_CAN_FEC_1_2 | FE_CAN_FEC_2_3 | FE_CAN_FEC_3_4 |
			FE_CAN_FEC_5_6 | FE_CAN_FEC_7_8 | FE_CAN_FEC_AUTO |
			FE_CAN_QPSK | FE_CAN_QAM_16 | FE_CAN_QAM_64 | FE_CAN_QAM_AUTO |
			FE_CAN_TRANSMISSION_MODE_AUTO |
			FE_CAN_GUARD_INTERVAL_AUTO |
			FE_CAN_RECOVER |
			FE_CAN_HIERARCHY_AUTO,
	},

	.release              = af903x_release,

	.init                 = af903x_init,
	.sleep                = af903x_sleep,

	.set_frontend         = af903x_set_frontend,
	.get_frontend         = af903x_get_frontend,

	.read_status          = af903x_read_status,
	.read_ber             = af903x_read_ber,
	.read_signal_strength = af903x_read_signal_strength,
	.read_snr             = af903x_read_snr,
	.read_ucblocks	      = af903x_read_unc_blocks,
};
MODULE_AUTHOR("Jimmy Chen <JyunYu.Chen@ite.com.tw>");
MODULE_DESCRIPTION("Driver for the AF903X demodulator");
MODULE_LICENSE("GPL");
