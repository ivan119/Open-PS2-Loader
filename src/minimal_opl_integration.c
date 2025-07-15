/*
 * Minimal OPL Integration Layer
 * Connects minimal OPL design with existing Open-PS2-Loader codebase
 */

#include "minimal_opl_config.h"
#include "include/opl.h"
#include "include/system.h"
#include "include/gui.h"
#include "include/bdmsupport.h"
#include "include/vmc_groups.h"
#include "include/sound.h"
#include "include/lang.h"
#include "include/config.h"

#include <loadcore.h>
#include <sifrpc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ============================================================================
// MINIMAL OPL GLOBAL VARIABLES
// ============================================================================

static int minimal_opl_initialized = 0;
static int microsd_detected = 0;
static int games_loaded = 0;

// ============================================================================
// MICROSD DETECTION AND INITIALIZATION
// ============================================================================

int minimal_opl_detect_microsd()
{
    printf("MINIMAL_OPL: Detecting microSD memory card adapter...\n");

    // Check if BDM is available and working
    if (!bdmDeviceListInitialized) {
        printf("MINIMAL_OPL: BDM not initialized, initializing...\n");
        bdmInitDevicesData();
    }

    // Check for mass storage devices (microSD)
    for (int i = 0; i < MAX_BDM_DEVICES; i++) {
        if (bdmDeviceList[i].enabled) {
            printf("MINIMAL_OPL: Found device %d: %s\n", i, bdmDeviceList[i].prefix);

            // Test if we can access the device
            char test_path[256];
            snprintf(test_path, sizeof(test_path), "%s", bdmDeviceList[i].prefix);

            // Try to open a test file
            FILE *test_file = fopen(test_path, "r");
            if (test_file) {
                fclose(test_file);
                microsd_detected = 1;
                printf("MINIMAL_OPL: MicroSD adapter detected and accessible\n");
                return 1;
            }
        }
    }

    printf("MINIMAL_OPL: No accessible microSD adapter found\n");
    return 0;
}

// ============================================================================
// MINIMAL SYSTEM INITIALIZATION
// ============================================================================

int minimal_opl_init_system()
{
    printf("MINIMAL_OPL: Initializing minimal system...\n");

    // Initialize SIF
    SifInitRpc(0);

    // Initialize basic modules only
    int modload_mask = SYS_LOAD_MC_MODULES | SYS_LOAD_ISOFS_MODULE;

    // Load essential modules
    sysLoadModules(modload_mask);

    // Initialize BDM for microSD support
    bdmInit();

    // Initialize VMC system
    vmc_groups_init();

    // Initialize basic GUI
    guiInit();

    // Initialize sound system
    soundInit();

    // Initialize language system
    langInit();

    // Initialize configuration
    configInit("mass0:");

    minimal_opl_initialized = 1;
    printf("MINIMAL_OPL: System initialized successfully\n");

    return 1;
}

// ============================================================================
// MINIMAL GAME SCANNING
// ============================================================================

int minimal_opl_scan_games()
{
    if (!minimal_opl_initialized) {
        printf("MINIMAL_OPL: System not initialized\n");
        return 0;
    }

    printf("MINIMAL_OPL: Scanning for games on microSD...\n");

    // Use existing BDM support to scan for games
    item_list_t *bdm_list = &bdmGameList;

    if (bdm_list->enabled) {
        // Initialize BDM game list
        bdm_list->itemInit(bdm_list);

        // Get game count
        int count = bdm_list->itemGetCount(bdm_list);
        printf("MINIMAL_OPL: Found %d games on microSD\n", count);

        games_loaded = count;
        return count;
    }

    printf("MINIMAL_OPL: No games found or BDM not available\n");
    return 0;
}

// ============================================================================
// MINIMAL GUI RENDERING
// ============================================================================

void minimal_opl_render_gui()
{
    if (!minimal_opl_initialized)
        return;

    // Clear screen
    guiClear();

    // Draw header
    guiDrawText(10, 10, "MINIMAL OPL - MicroSD Loader", 0xFFFFFF);
    guiDrawText(10, 30, "==========================================", 0x888888);

    // Draw microSD info
    char info_text[256];
    snprintf(info_text, sizeof(info_text), "MicroSD: %d games found", games_loaded);
    guiDrawText(10, 50, info_text, 0x00FF00);

    // Draw game list
    if (bdmGameList.enabled) {
        int count = bdmGameList.itemGetCount(&bdmGameList);

        for (int i = 0; i < count && i < 20; i++) {
            char game_name[256];
            bdmGameList.itemGetName(&bdmGameList, i, game_name, sizeof(game_name));

            int y_pos = 80 + (i * 20);
            guiDrawText(20, y_pos, game_name, 0xFFFFFF);
        }
    }

    // Draw controls
    guiDrawText(10, 400, "Controls:", 0xFFFF00);
    guiDrawText(20, 420, "Up/Down: Select game", 0xCCCCCC);
    guiDrawText(20, 440, "X: Launch game", 0xCCCCCC);
    guiDrawText(20, 460, "Triangle: Exit", 0xCCCCCC);

    // Update display
    guiUpdate();
}

// ============================================================================
// MINIMAL GAME LAUNCHING
// ============================================================================

int minimal_opl_launch_game(int game_index)
{
    if (!minimal_opl_initialized) {
        printf("MINIMAL_OPL: System not initialized\n");
        return -1;
    }

    if (game_index < 0 || game_index >= games_loaded) {
        printf("MINIMAL_OPL: Invalid game index: %d\n", game_index);
        return -1;
    }

    printf("MINIMAL_OPL: Launching game %d\n", game_index);

    // Get game name for VMC creation
    char game_name[256];
    bdmGameList.itemGetName(&bdmGameList, game_index, game_name, sizeof(game_name));

    // Create VMC for the game
    vmc_groups_create_vmc(game_name);

    // Launch the game using existing BDM launch function
    int result = bdmGameList.itemLaunch(&bdmGameList, game_index);

    if (result == 1) {
        printf("MINIMAL_OPL: Game launched successfully\n");
    } else {
        printf("MINIMAL_OPL: Failed to launch game\n");
    }

    return result;
}

// ============================================================================
// MINIMAL INPUT HANDLING
// ============================================================================

int minimal_opl_handle_input()
{
    // Simple input handling for minimal GUI
    // This would integrate with the existing pad input system

    // For now, return 0 to continue, 1 to exit
    return 0;
}

// ============================================================================
// MINIMAL OPL MAIN LOOP
// ============================================================================

int minimal_opl_main_loop()
{
    printf("MINIMAL_OPL: Starting main loop...\n");

    int selected_game = 0;
    int running = 1;

    while (running) {
        // Render GUI
        minimal_opl_render_gui();

        // Handle input
        int input_result = minimal_opl_handle_input();

        if (input_result == 1) {
            running = 0;
        }

        // Small delay to prevent excessive CPU usage
        // This would use proper timing functions in real implementation
    }

    printf("MINIMAL_OPL: Exiting main loop\n");
    return 0;
}

// ============================================================================
// MINIMAL OPL CLEANUP
// ============================================================================

void minimal_opl_cleanup()
{
    printf("MINIMAL_OPL: Cleaning up...\n");

    // Cleanup GUI
    guiEnd();

    // Cleanup sound
    soundEnd();

    // Cleanup VMC
    vmc_groups_end();

    // Cleanup BDM
    bdmEnd();

    minimal_opl_initialized = 0;
    microsd_detected = 0;
    games_loaded = 0;

    printf("MINIMAL_OPL: Cleanup complete\n");
}

// ============================================================================
// MINIMAL OPL ENTRY POINT
// ============================================================================

int minimal_opl_start()
{
    printf("MINIMAL_OPL: Starting minimal PS2 loader...\n");

    // Initialize system
    if (!minimal_opl_init_system()) {
        printf("MINIMAL_OPL: Failed to initialize system\n");
        return -1;
    }

    // Detect microSD
    if (!minimal_opl_detect_microsd()) {
        printf("MINIMAL_OPL: No microSD adapter detected\n");
        minimal_opl_cleanup();
        return -1;
    }

    // Scan for games
    if (minimal_opl_scan_games() == 0) {
        printf("MINIMAL_OPL: No games found on microSD\n");
        minimal_opl_cleanup();
        return -1;
    }

    // Run main loop
    int result = minimal_opl_main_loop();

    // Cleanup
    minimal_opl_cleanup();

    printf("MINIMAL_OPL: Exiting...\n");
    return result;
}