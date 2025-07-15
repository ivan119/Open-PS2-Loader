/*
 * Minimal OPL Header File
 * Declares functions for minimal OPL integration
 */

#ifndef MINIMAL_OPL_H
#define MINIMAL_OPL_H

#include "minimal_opl_config.h"

// ============================================================================
// MINIMAL OPL CORE FUNCTIONS
// ============================================================================

/**
 * Main entry point for minimal OPL
 * @return 0 on success, -1 on failure
 */
int minimal_opl_start(void);

/**
 * Initialize minimal OPL system
 * @return 1 on success, 0 on failure
 */
int minimal_opl_init_system(void);

/**
 * Detect microSD memory card adapter
 * @return 1 if detected, 0 if not found
 */
int minimal_opl_detect_microsd(void);

/**
 * Scan for games on microSD
 * @return Number of games found
 */
int minimal_opl_scan_games(void);

/**
 * Launch a game by index
 * @param game_index Index of game to launch
 * @return 1 on success, -1 on failure
 */
int minimal_opl_launch_game(int game_index);

/**
 * Render minimal GUI
 */
void minimal_opl_render_gui(void);

/**
 * Handle input for minimal GUI
 * @return 0 to continue, 1 to exit
 */
int minimal_opl_handle_input(void);

/**
 * Main loop for minimal OPL
 * @return 0 on normal exit, -1 on error
 */
int minimal_opl_main_loop(void);

/**
 * Cleanup minimal OPL resources
 */
void minimal_opl_cleanup(void);

// ============================================================================
// MINIMAL OPL UTILITY FUNCTIONS
// ============================================================================

/**
 * Check if minimal OPL is initialized
 * @return 1 if initialized, 0 if not
 */
int minimal_opl_is_initialized(void);

/**
 * Get number of games loaded
 * @return Number of games found
 */
int minimal_opl_get_game_count(void);

/**
 * Get microSD detection status
 * @return 1 if detected, 0 if not
 */
int minimal_opl_is_microsd_detected(void);

// ============================================================================
// MINIMAL OPL CONFIGURATION
// ============================================================================

/**
 * Set minimal OPL configuration
 * @param config Configuration structure
 * @return 1 on success, 0 on failure
 */
int minimal_opl_set_config(const void *config);

/**
 * Get minimal OPL configuration
 * @param config Configuration structure to fill
 * @return 1 on success, 0 on failure
 */
int minimal_opl_get_config(void *config);

// ============================================================================
// MINIMAL OPL DEBUG FUNCTIONS
// ============================================================================

/**
 * Enable/disable debug output
 * @param enable 1 to enable, 0 to disable
 */
void minimal_opl_set_debug(int enable);

/**
 * Print debug information
 * @param message Debug message
 */
void minimal_opl_debug_print(const char *message);

// ============================================================================
// MINIMAL OPL ERROR HANDLING
// ============================================================================

/**
 * Get last error code
 * @return Error code
 */
int minimal_opl_get_last_error(void);

/**
 * Get last error message
 * @return Error message string
 */
const char *minimal_opl_get_last_error_message(void);

/**
 * Clear last error
 */
void minimal_opl_clear_error(void);

// ============================================================================
// MINIMAL OPL VERSION INFORMATION
// ============================================================================

/**
 * Get minimal OPL version string
 * @return Version string
 */
const char *minimal_opl_get_version(void);

/**
 * Get minimal OPL build date
 * @return Build date string
 */
const char *minimal_opl_get_build_date(void);

// ============================================================================
// MINIMAL OPL COMPATIBILITY
// ============================================================================

/**
 * Check PS2 model compatibility
 * @param model PS2 model number
 * @return 1 if compatible, 0 if not
 */
int minimal_opl_check_compatibility(int model);

/**
 * Get recommended settings for PS2 model
 * @param model PS2 model number
 * @param settings Settings structure to fill
 * @return 1 on success, 0 on failure
 */
int minimal_opl_get_recommended_settings(int model, void *settings);

#endif // MINIMAL_OPL_H