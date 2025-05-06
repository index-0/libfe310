/* See LICENSE file for copyright and license details. */

#ifndef LIBFE310_SPI_H
#define LIBFE310_SPI_H

#include <fe310/atomic.h>
#include <fe310/periph.h>
#include <fe310/types.h>
#include <fe310/vendor/spi.h>

#define SPI_CSDEF_CS0(state) ((state) ? BITMASK(0) : 0UL)
#define SPI_CSDEF_CS1(state) ((state) ? BITMASK(1) : 0UL)
#define SPI_CSDEF_CS2(state) ((state) ? BITMASK(2) : 0UL)
#define SPI_CSDEF_CS3(state) ((state) ? BITMASK(3) : 0UL)

typedef enum {
	SPI_ID_CS0 = 0,
	SPI_ID_CS1 = 1,
	SPI_ID_CS2 = 2,
	SPI_ID_CS3 = 3,
} SpiCsId;

typedef enum {
	SPI_CSMODE_AUTO = 0,
	SPI_CSMODE_HOLD = 2,
	SPI_CSMODE_OFF = 3,
} SpiCsMode;

typedef enum {
	SPI_DIR_RX = 0,
	SPI_DIR_TX = 8,
} SpiDir;

typedef enum {
	SPI_ENDIAN_MSB = 0,
	SPI_ENDIAN_LSB = 4,
} SpiEndian;

typedef enum {
	SPI_PROTO_S = 0,
	SPI_PROTO_D = 1,
	SPI_PROTO_Q = 2,
} SpiProto;

typedef enum {
	SPI_SCKMODE_0 = 0,
	SPI_SCKMODE_1 = 1,
	SPI_SCKMODE_2 = 2,
	SPI_SCKMODE_3 = 3,
} SpiSckMode;

typedef struct Spi {
	volatile u32 sckdiv;
	volatile u32 sckmode;
	u32 reserved0[2];
	volatile u32 csid;
	volatile u32 csdef;
	volatile u32 csmode;
	u32 reserved1[3];
	volatile u32 delay0;
	volatile u32 delay1;
	u32 reserved2[4];
	volatile u32 fmt;
	u32 reserved3;
	volatile u32 txdata;
	volatile u32 rxdata;
	volatile u32 txmark;
	volatile u32 rxmark;
	u32 reserved4[2];
	volatile u32 fctrl;
	volatile u32 ffmt;
	u32 reserved5[2];
	volatile u32 ie;
	volatile u32 ip;
} Spi;

extern volatile Spi *const spi0;
extern volatile Spi *const spi1;
extern volatile Spi *const spi2;

/*
 * SERIAL CLOCK DIVISOR REGISTER (sckdiv)
 */

static inline void
spi_set_sckdiv(volatile Spi *spi, u32 div)
{
	spi->sckdiv = div;
}

static inline u32
spi_get_sckdiv(volatile Spi *spi)
{
	return spi->sckdiv;
}

/*
 * SERIAL CLOCK MODE REGISTER (sckmode)
 */

static inline void
spi_set_sckmode(volatile Spi *spi, SpiSckMode mode)
{
	spi->sckmode = mode;
}

static inline SpiSckMode
spi_get_sckmode(volatile Spi *spi)
{
	return spi->sckmode;
}

/*
 * CHIP SELECT ID REGISTER (csid)
 */

static inline void
spi_set_csid(volatile Spi *spi, SpiCsId csid)
{
	if ((u32)spi != SPI1_BASE) return;
	spi->csid = csid;
}

static inline SpiCsId
spi_get_csid(volatile Spi *spi)
{
	return spi->csid;
}

/*
 * CHIP SELECT DEFAULT REGISTER (csdef)
 */

static inline void
spi_set_csdef(volatile Spi *spi, u32 csdef)
{
	spi->csdef = csdef;
}

static inline u32
spi_get_csdef(volatile Spi *spi)
{
	return spi->csdef;
}

/*
 * CHIP SELECT MODE REGISTER (csmode)
 */

static inline void
spi_set_csmode(volatile Spi *spi, SpiCsMode mode)
{
	spi->csmode = mode;
}

static inline SpiCsMode
spi_get_csmode(volatile Spi *spi)
{
	return spi->csmode;
}

/*
 * DELAY CONTROL REGISTERS (delay0 and delay1)
 */

static inline void
spi_set_delay0_cssck(volatile Spi *spi, u8 cssck)
{
	spi->delay0 = (spi->delay0 & ~SPI_DELAY0_CSSCK) |
		(cssck & SPI_DELAY0_CSSCK);
}

static inline u8
spi_get_delay0_cssck(volatile Spi *spi)
{
	return spi->delay0;
}

static inline void
spi_set_delay0_sckcs(volatile Spi *spi, u8 sckcs)
{
	spi->delay0 = (spi->delay0 & ~SPI_DELAY0_SCKCS) |
		((sckcs << CTZ(SPI_DELAY0_SCKCS)) & SPI_DELAY0_SCKCS);
}

static inline u8
spi_get_delay0_sckcs(volatile Spi *spi)
{
	return spi->delay0 >> CTZ(SPI_DELAY0_SCKCS);
}

static inline void
spi_delay0(volatile Spi *spi, u8 cssck, u8 sckcs)
{
	spi->delay0 = (cssck & SPI_DELAY0_CSSCK) |
		((sckcs << CTZ(SPI_DELAY0_SCKCS)) & SPI_DELAY0_SCKCS);
}

static inline void
spi_set_delay1_intercs(volatile Spi *spi, u8 intercs)
{
	spi->delay1 = (spi->delay1 & ~SPI_DELAY1_INTERCS) |
		(intercs & SPI_DELAY1_INTERCS);
}

static inline u8
spi_get_delay1_intercs(volatile Spi *spi)
{
	return spi->delay1;
}

static inline void
spi_set_delay1_interxfr(volatile Spi *spi, u8 xfr)
{
	spi->delay1 = (spi->delay1 & ~SPI_DELAY1_INTERXFR) |
		((xfr << CTZ(SPI_DELAY1_INTERXFR)) & SPI_DELAY1_INTERXFR);
}

static inline u8
spi_get_delay1_interxfr(volatile Spi *spi)
{
	return spi->delay1 >> CTZ(SPI_DELAY1_INTERXFR);
}

static inline void
spi_delay1(volatile Spi *spi, u8 cs, u8 xfr)
{
	spi->delay1 = (cs & SPI_DELAY1_INTERCS) |
		((xfr << CTZ(SPI_DELAY1_INTERXFR)) & SPI_DELAY1_INTERXFR);
}

/*
 * FRAME FORMAT REGISTER (fmt)
 */

static inline void
spi_set_fmt_proto(volatile Spi *spi, SpiProto proto)
{
	proto = (proto > SPI_PROTO_Q) ? SPI_PROTO_Q : proto;
	spi->fmt = (spi->fmt & ~SPI_FMT_PROTO) |
		(proto & SPI_FMT_PROTO);
}

static inline SpiProto
spi_get_fmt_proto(volatile Spi *spi)
{
	return spi->fmt & SPI_FMT_PROTO;
}

static inline void
spi_set_fmt_endian(volatile Spi *spi, SpiEndian endian)
{
	spi->fmt = (spi->fmt & ~SPI_FMT_ENDIAN) |
		(endian & SPI_FMT_ENDIAN);
}

static inline SpiEndian
spi_get_fmt_endian(volatile Spi *spi)
{
	return spi->fmt & SPI_FMT_ENDIAN;
}

static inline void
spi_set_fmt_dir(volatile Spi *spi, SpiDir dir)
{
	spi->fmt = (spi->fmt & ~SPI_FMT_DIR) |
		(dir & SPI_FMT_DIR);
}

static inline SpiDir
spi_get_fmt_dir(volatile Spi *spi)
{
	return spi->fmt & SPI_FMT_DIR;
}

static inline void
spi_set_fmt_len(volatile Spi *spi, u32 len)
{
	len = (len > SPI_FMT_LEN_MAX) ? SPI_FMT_LEN_MAX : len;
	spi->fmt = (spi->fmt & ~SPI_FMT_LEN) |
		((len << CTZ(SPI_FMT_LEN)) & SPI_FMT_LEN);
}

static inline u32
spi_get_fmt_len(volatile Spi *spi)
{
	return (spi->fmt & SPI_FMT_LEN) >> CTZ(SPI_FMT_LEN);
}

static inline void
spi_fmt(volatile Spi *spi, SpiProto proto, SpiEndian endian, SpiDir dir,
		u32 len)
{
	len = (len > SPI_FMT_LEN_MAX) ? SPI_FMT_LEN_MAX : len;
	proto = (proto > SPI_PROTO_Q) ? SPI_PROTO_Q : proto;
	spi->fmt = (proto & SPI_FMT_PROTO) |
		(endian & SPI_FMT_ENDIAN) |
		(dir & SPI_FMT_DIR) |
		((len << CTZ(SPI_FMT_LEN)) & SPI_FMT_LEN);
}

/*
 * TRANSMIT DATA REGISTER (txdata)
 */

static inline void
spi_set_txdata(volatile Spi *spi, u8 c) {
	s32 r;
	do
		r = amoor_w(&spi->txdata, c);
	while (r < 0);
}

static inline bool
spi_is_txdata_full(volatile Spi *spi)
{
	return ((s32)spi->txdata >= 0);
}

/*
 * RECEIVE DATA REGISTER (rxdata)
 */

static inline u8
spi_get_rxdata(volatile Spi *spi)
{
	s32 r;
	do
		r = spi->rxdata;
	while (r < 0);
	return r;
}

static inline bool
spi_is_rxdata_empty(volatile Spi *spi)
{
	return ((s32)spi->rxdata >= 0);
}

/*
 * TRANSMIT WATERMARK REGISTER (txmark)
 */

static inline void
spi_set_txmark(volatile Spi *spi, WaterMarkLevel wm)
{
	spi->txmark = wm;
}

static inline WaterMarkLevel
spi_get_txmark(volatile Spi *spi)
{
	return spi->txmark;
}

/*
 * RECEIVE WATERMARK REGISTER (rxmark)
 */

static inline void
spi_set_rxmark(volatile Spi *spi, WaterMarkLevel wm)
{
	spi->rxmark = wm;
}

static inline WaterMarkLevel
spi_get_rxmark(volatile Spi *spi)
{
	return spi->rxmark;
}

/*
 * FLASH INTERFACE CONTROL REGISTER (fctrl)
 */

static inline void
spi_set_fctrl_en(volatile Spi *spi, bool en)
{
	if ((u32)spi != SPI0_BASE) return;
	spi->fctrl = en ? 1 : 0;
}

static inline bool
spi_is_fctrl_en(volatile Spi *spi)
{
	return (spi->fctrl & SPI_FCTRL_EN) != 0;
}

/*
 * FLASH INSTRUCTION FORMAT REGISTER (ffmt)
 */

static inline void
spi_set_ffmt_cmd_en(volatile Spi *spi, bool en)
{
	if (en)
		spi->ffmt |= SPI_FFMT_CMD_EN;
	else
		spi->ffmt &= ~SPI_FFMT_CMD_EN;
}

static inline bool
spi_is_ffmt_cmd_en(volatile Spi *spi)
{
	return (spi->ffmt & SPI_FFMT_CMD_EN) != 0;
}

static inline void
spi_set_ffmt_addr_len(volatile Spi *spi, u32 len)
{
	spi->ffmt = (spi->ffmt & ~SPI_FFMT_ADDR_LEN) |
		((len << CTZ(SPI_FFMT_ADDR_LEN)) & SPI_FFMT_ADDR_LEN);
}

static inline u32
spi_get_ffmt_addr_len(volatile Spi *spi)
{
	return (spi->ffmt & SPI_FFMT_ADDR_LEN) >> CTZ(SPI_FFMT_ADDR_LEN);
}

static inline void
spi_set_ffmt_pad_cnt(volatile Spi *spi, u32 pad)
{
	spi->ffmt = (spi->ffmt & ~SPI_FFMT_PAD_CNT) |
		((pad << CTZ(SPI_FFMT_PAD_CNT)) & SPI_FFMT_PAD_CNT);
}

static inline u32
spi_get_ffmt_pad_cnt(volatile Spi *spi)
{
	return (spi->ffmt & SPI_FFMT_PAD_CNT) >> CTZ(SPI_FFMT_PAD_CNT);
}

static inline void
spi_set_ffmt_cmd_proto(volatile Spi *spi, SpiProto proto)
{
	spi->ffmt = (spi->ffmt & ~SPI_FFMT_CMD_PROTO) |
		((proto << CTZ(SPI_FFMT_CMD_PROTO)) & SPI_FFMT_CMD_PROTO);
}

static inline SpiProto
spi_get_ffmt_cmd_proto(volatile Spi *spi)
{
	return (spi->ffmt & SPI_FFMT_CMD_PROTO) >> CTZ(SPI_FFMT_CMD_PROTO);
}

static inline void
spi_set_ffmt_addr_proto(volatile Spi *spi, SpiProto proto)
{
	spi->ffmt = (spi->ffmt & ~SPI_FFMT_ADDR_PROTO) |
		((proto << CTZ(SPI_FFMT_ADDR_PROTO)) & SPI_FFMT_ADDR_PROTO);
}

static inline SpiProto
spi_get_ffmt_addr_proto(volatile Spi *spi)
{
	return (spi->ffmt & SPI_FFMT_ADDR_PROTO) >> CTZ(SPI_FFMT_ADDR_PROTO);
}

static inline void
spi_set_ffmt_data_proto(volatile Spi *spi, SpiProto proto)
{
	spi->ffmt = (spi->ffmt & ~SPI_FFMT_DATA_PROTO) |
		((proto << CTZ(SPI_FFMT_DATA_PROTO)) & SPI_FFMT_DATA_PROTO);
}

static inline SpiProto
spi_get_ffmt_data_proto(volatile Spi *spi)
{
	return (spi->ffmt & SPI_FFMT_DATA_PROTO) >>
		CTZ(SPI_FFMT_DATA_PROTO);
}

static inline void
spi_set_ffmt_cmd_code(volatile Spi *spi, u8 code)
{
	spi->ffmt = (spi->ffmt & ~SPI_FFMT_CMD_CODE) |
		(code << CTZ(SPI_FFMT_CMD_CODE));
}

static inline u8
spi_get_ffmt_cmd_code(volatile Spi *spi)
{
	return spi->ffmt >> CTZ(SPI_FFMT_CMD_CODE);
}

static inline void
spi_set_ffmt_pad_code(volatile Spi *spi, u8 code)
{
	spi->ffmt = (spi->ffmt & ~SPI_FFMT_PAD_CODE) |
		(code << CTZ(SPI_FFMT_PAD_CODE));
}

static inline u8
spi_get_ffmt_pad_code(volatile Spi *spi)
{
	return spi->ffmt >> CTZ(SPI_FFMT_PAD_CODE);
}

static inline void
spi_ffmt(volatile Spi *spi, bool cmd_en, u32 addr_len, u32 pad_cnt,
		SpiProto cproto, SpiProto aproto, SpiProto dproto,
		u8 cmd_code, u8 pad_code)
{
	spi->ffmt = (cmd_en ? SPI_FFMT_CMD_EN : 0) |
		((addr_len << CTZ(SPI_FFMT_ADDR_LEN)) & SPI_FFMT_ADDR_LEN) |
		((pad_cnt << CTZ(SPI_FFMT_PAD_CNT)) & SPI_FFMT_PAD_CNT) |
		((cproto << CTZ(SPI_FFMT_CMD_PROTO)) & SPI_FFMT_CMD_PROTO) |
		((aproto << CTZ(SPI_FFMT_ADDR_PROTO)) & SPI_FFMT_ADDR_PROTO) |
		((dproto << CTZ(SPI_FFMT_DATA_PROTO)) & SPI_FFMT_DATA_PROTO) |
		(cmd_code << CTZ(SPI_FFMT_CMD_CODE)) |
		(pad_code << CTZ(SPI_FFMT_PAD_CODE));
}

/*
 * INTERRUPT ENABLE REGISTER (ie)
 */

static inline void
spi_set_txwm_ie(volatile Spi *spi, bool en)
{
	if (en)
		spi->ie |= SPI_IE_TXWM;
	else
		spi->ie &= ~SPI_IE_TXWM;
}

static inline bool
spi_is_txwm_ie(volatile Spi *spi)
{
	return (spi->ie & SPI_IE_TXWM) != 0;
}

static inline void
spi_set_rxwm_ie(volatile Spi *spi, bool en)
{
	if (en)
		spi->ie |= SPI_IE_RXWM;
	else
		spi->ie &= ~SPI_IE_RXWM;
}

static inline bool
spi_is_rxwm_ie(volatile Spi *spi)
{
	return (spi->ie & SPI_IE_RXWM) != 0;
}

/*
 * INTERRUPT PENDING REGISTER (ip)
 */

static inline bool
spi_is_txwm_ip(volatile Spi *spi)
{
	return spi->ip & SPI_IP_TXWM;
}

static inline bool
spi_is_rxwm_ip(volatile Spi *spi)
{
	return (spi->ip & SPI_IP_RXWM) != 0;
}

#endif /* LIBFE310_SPI_H */
