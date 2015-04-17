mod_rook_api.la: mod_rook_api.slo
	$(SH_LINK) -rpath $(libexecdir) -module -avoid-version  mod_rook_api.lo
DISTCLEAN_TARGETS = modules.mk
shared =  mod_rook_api.la
