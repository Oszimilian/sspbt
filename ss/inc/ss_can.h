#ifndef _SS_CAN_H_
#define _SS_CAN_H_

struct can_tx_msg {
	uint32_t std_id;
	uint32_t ext_id;
	uint8_t ide;
	uint8_t rtr;
	uint8_t dlc;
	uint8_t data[8];
};

struct can_rx_msg {
	uint32_t std_id;
	uint32_t ext_id;
	uint8_t ide;
	uint8_t rtr;
	uint8_t dlc;
	uint8_t data[8];
	uint8_t fmi;
};

struct can_tx_msg can_tx_msg;
struct can_rx_msg can_rx_msg;

int8_t ss_init_can(uint8_t can_interface_id, uint32_t baudrate);

int8_t ss_send_can(struct can_tx_msg* msg);

void usb_lp_can_rx0_isr(void);


#endif