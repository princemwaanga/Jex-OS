void shutdown_power_off (void)
{
  const char s[] = "Shutdown";
  const char *p;


  /* This is a special power-off sequence supported by Bochs and
     QEMU, but not by physical hardware. */
  for (p = s; *p != '\0'; p++)
    outb (0x8900, *p);

  /* For newer versions of qemu, you must run with -device
   * isa-debug-exit, which exits on any write to an IO port (by
   * default 0x501).  Qemu's exit code is double the value plus one,
   * so there is no way to exit cleanly.  We use 0x31 which should
   * result in a qemu exit code of 0x63.  */
  outb (0x501, 0x31);

  /* This will power off a VMware VM if "gui.exitOnCLIHLT = TRUE"
     is set in its configuration file.  (The "pintos" script does
     that automatically.)  */
  asm volatile ("cli; hlt" : : : "memory");

  /* None of those worked. */
  kprint("still running...\n");
  for (;;);
}