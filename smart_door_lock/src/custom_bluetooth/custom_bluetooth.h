/**
 * @file custom_bluetooth.h
 * @brief Bluetooth SMP Advertisement Control
 *
 * This file provides functions for starting and managing Bluetooth Low Energy
 * (BLE) advertisements so the Simple Management Protocol (SMP) could be used. It is
 * responsible for configuring and broadcasting advertisement packets to allow
 * other BLE devices to discover and connect to the local device.
 */

#ifndef CUSTOM_BLUETOOTH_H_
#define CUSTOM_BLUETOOTH_H_

/**
 * @brief Start Simple Management Protocol (SMP) Bluetooth Advertisements.
 *
 * @return None.
 */
void start_smp_bluetooth_adverts();

/**
 * @brief Stop Simple Management Protocol (SMP) Bluetooth Advertisements.
 *
 * @return None.
 */
void stop_smp_bluetooth_adverts();

#endif  // CUSTOM_BLUETOOTH_H_