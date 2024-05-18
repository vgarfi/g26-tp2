GLOBAL rtc_get_seconds
GLOBAL rtc_get_minutes
GLOBAL rtc_get_hour
GLOBAL rtc_get_day
GLOBAL rtc_get_month
GLOBAL rtc_get_year

section .text
rtc_get_seconds:
    cli

    mov al, 0x0B
    out 70h, al
    in al, 71h
    or al, 4
    out 71h, al     ; Sets Seconds to be returned in binary

    mov al, 0x00
    out 70h, al
    in al, 71h

    sti

    ret

rtc_get_minutes:
    cli

    mov al, 0x0B
    out 70h, al
    in al, 71h
    or al, 4
    out 71h, al     ; Sets Minutes to be returned in binary

    mov al, 0x02
    out 70h, al
    in al, 71h

    sti
    ret

rtc_get_hour:
    mov al, 0x0B
    out 70h, al
    in al, 71h
    or al, 4
    out 71h, al     ; Sets Hours to be returned in binary

    mov al, 0x04
    out 70h, al
    in al, 71h

    sti
    ret

rtc_get_day:        ;; Returns day of the month
    mov al, 0x0B
    out 70h, al
    in al, 71h
    or al, 4
    out 71h, al     ; Sets Day to be returned in binary

    mov al, 0x07
    out 70h, al
    in al, 71h

    sti
    ret

rtc_get_month:
    mov al, 0x0B
    out 70h, al
    in al, 71h
    or al, 4
    out 71h, al     ; Sets Month to be returned in binary

    mov al, 0x08
    out 70h, al
    in al, 71h

    sti
    ret

rtc_get_year:
    mov al, 0x0B
    out 70h, al
    in al, 71h
    or al, 4
    out 71h, al     ; Sets Year to be returned in binary

    mov al, 0x09
    out 70h, al
    in al, 71h

    sti
    ret