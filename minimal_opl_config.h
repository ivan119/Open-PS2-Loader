/*
 * Minimal OPL Configuration for MicroSD Memory Card Adapter
 * Removes unnecessary features to create a lightweight PS2 loader
 */

#ifndef MINIMAL_OPL_CONFIG_H
#define MINIMAL_OPL_CONFIG_H

// ============================================================================
// ENABLED FEATURES (Only what's needed for microSD memory card adapter)
// ============================================================================

#define ENABLE_MCEMU     1 // Memory card emulation
#define ENABLE_BDM       1 // Block device manager (for microSD)
#define ENABLE_ISOFS     1 // ISO file system support
#define ENABLE_CDVDMAN   1 // CD/DVD emulation
#define ENABLE_VMC       1 // Virtual memory cards
#define ENABLE_BASIC_GUI 1 // Minimal GUI
#define ENABLE_SOUND     1 // Basic sound effects

// ============================================================================
// DISABLED FEATURES (Removed for minimal footprint)
// ============================================================================

#define ENABLE_SMB          0 // Network SMB support
#define ENABLE_HDD          0 // Hard disk support
#define ENABLE_USB_MASS     0 // USB mass storage
#define ENABLE_NETWORK      0 // Network features
#define ENABLE_CHEAT_ENGINE 0 // Cheat engine
#define ENABLE_COMPLEX_GUI  0 // Complex themes/skins
#define ENABLE_DEBUG        0 // Debug features
#define ENABLE_PADEMU       0 // Controller emulation
#define ENABLE_ILINK        0 // iLink support
#define ENABLE_MX4SIO       0 // MX4SIO support

// ============================================================================
// MICROSD OPTIMIZATION SETTINGS
// ============================================================================

#define MICROSD_BUFFER_SIZE 8192  // Optimized buffer size for microSD
#define MICROSD_READ_AHEAD  4     // Read ahead sectors
#define MICROSD_CACHE_SIZE  32768 // Cache size for better performance

// Memory card adapter detection
#define MEMORY_CARD_ADAPTER_SD   1 // Support SD cards
#define MEMORY_CARD_ADAPTER_SDHC 1 // Support SDHC cards
#define MEMORY_CARD_ADAPTER_SDXC 0 // SDXC support (optional)

// ============================================================================
// GUI SIMPLIFICATION
// ============================================================================

#define GUI_MAX_GAMES         100 // Maximum games to display
#define GUI_SIMPLE_LAYOUT     1   // Use simple layout
#define GUI_REMOVE_ANIMATIONS 1   // Remove animations for speed
#define GUI_BASIC_THEME       1   // Use basic theme only

// ============================================================================
// VMC (Virtual Memory Card) SETTINGS
// ============================================================================

#define VMC_DEFAULT_SIZE 8  // Default VMC size in MB
#define VMC_MAX_SIZE     64 // Maximum VMC size in MB
#define VMC_AUTO_CREATE  1  // Auto-create VMC files

// ============================================================================
// PERFORMANCE OPTIMIZATIONS
// ============================================================================

#define OPTIMIZE_MEMORY_USAGE   1 // Reduce memory footprint
#define OPTIMIZE_LOADING_SPEED  1 // Optimize for faster loading
#define REMOVE_UNUSED_MODULES   1 // Remove unused modules
#define SIMPLIFY_ERROR_HANDLING 1 // Simplify error handling

// ============================================================================
// COMPATIBILITY SETTINGS
// ============================================================================

#define COMPAT_PS2_GAMES 1 // PS2 game compatibility
#define COMPAT_PS1_GAMES 0 // PS1 game support (disabled)
#define COMPAT_DVD_VIDEO 0 // DVD video support (disabled)

#endif // MINIMAL_OPL_CONFIG_H