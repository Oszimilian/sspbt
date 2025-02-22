#ifndef _SS_CAN_H_
#define _SS_CAN_H_

#include <inttypes.h>
#include <stddef.h>

#define FIFO_SIZE 5

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


struct Fifo {
    struct can_rx_msg can_frames[FIFO_SIZE];
    int front;
    int rear;
};

extern struct Fifo can_receive_fifos[2];

int8_t ss_enable_can_rcc(uint8_t can_interface_id);

int8_t ss_enable_can_gpios(uint8_t can_interface_id);

int8_t ss_init_can_nvic(uint8_t can_interface_id, uint8_t prio);

int8_t ss_can_get_bit_timings(uint32_t baudrate, uint32_t* sjw, uint32_t* tseg1, uint32_t* tseg2, uint32_t* prescaler);

uint32_t ss_get_can_port_from_id(uint8_t can_interface_id);

int8_t ss_can_init(uint8_t can_interface_id, uint32_t baudrate);

int8_t ss_can_read(uint8_t can_interface_id, struct can_rx_msg* can_frame);

int8_t ss_can_send(uint8_t can_interface_id, struct can_tx_msg* can_frame);

int8_t ss_can_add_messages(uint32_t* ids, uint8_t len);

void usb_lp_can_rx0_isr(void);




void init_fifo(struct Fifo* fifo);
uint8_t is_fifo_empty(struct Fifo* fifo);
uint8_t is_fifo_full(struct Fifo* fifo);
int8_t fifo_add_can_frame(struct Fifo* fifo, struct can_rx_msg* can_frame);
int8_t fifo_remove_can_frame(struct Fifo* fifo, struct can_rx_msg* can_frame);



#endif