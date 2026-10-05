#ifndef CONFIG_H
#define CONFIG_H

#define UART_BAUD 9600UL

/*
 * Soil moisture sensor calibration.
 *
 * Higher ADC values = drier soil.
 * Lower ADC values  = wetter soil.
 *
 * Current bench-test observations:
 *   air / very dry: ~1023
 *   wet probe:      ~250-360
 *
 * These thresholds are initial values and should later
 * be calibrated using actual dry and wet soil.
 */
#define SOIL_DRY_THRESHOLD 700U
#define SOIL_WET_THRESHOLD 550U

#define SOIL_SAMPLE_COUNT 16U

/*
 * Safety limits.
 *
 * The pump will never run continuously for longer than
 * PUMP_MAX_ON_SECONDS.
 */
#define PUMP_MAX_ON_SECONDS 3U

/*
 * Wait before allowing another watering cycle.
 */
#define PUMP_COOLDOWN_SECONDS 60U

#endif
