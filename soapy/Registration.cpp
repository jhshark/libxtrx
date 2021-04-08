#include "SoapyXTRX.h"
#include <SoapySDR/Registry.hpp>
#include <SoapySDR/Logger.hpp>

static SoapySDR::KwargsList findIConnection(const SoapySDR::Kwargs &matchArgs)
{
    SoapySDR::KwargsList results;
    SoapySDR::KwargsList results2;

	xtrx_device_info_t devs[64];
	int res = xtrx_discovery(devs, 64);
	if (res < 0)
		return results;

	for (int i = 0; i < res; i++) {
		SoapySDR::Kwargs xtrxArgs;
		xtrxArgs["type"] = "xtrx";
		xtrxArgs["dev"] = devs[i].uniqname;

		xtrxArgs["module"] = "SoapyXTRX";
		xtrxArgs["media"] = devs[i].proto;
		xtrxArgs["name"] = "XTRX";
		xtrxArgs["addr"] = devs[i].uniqname;
		xtrxArgs["serial"] = devs[i].serial;

		xtrxArgs["driver"] = "xtrx";
		xtrxArgs["label"] = std::string("XTRX: ") + devs[i].uniqname + " (" + devs[i].speed + ")";
		results2.push_back(xtrxArgs);
		if (xtrxArgs["dev"] == matchArgs["dev"])
			results2[i] = results;
	}
	
    return results;
}

static SoapySDR::Device *makeIConnection(const SoapySDR::Kwargs &args)
{
    return new SoapyXTRX(args);
}

static SoapySDR::Registry registerIConnection("xtrx", &findIConnection, &makeIConnection, SOAPY_SDR_ABI_VERSION);


