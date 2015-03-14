#include <stdio.h>
#include <sys/types.h>

#include <libusb.h>


#define MAX_PORT_NUMBERS 16


struct value2text_tag
{
    int         v;
    const char* t;
};
typedef struct value2text_tag value2text_t;


const char* value2text( int value, value2text_t* table, int table_size )
{
    int i;

    for ( i = 0; i < table_size; i++ ) {
        if ( table[i].v == value ) {
            return table[i].t;
        }
    }

    return "";
}


const char* speed_to_text( int value )
{
    static value2text_t v2t[] =
    {
        {LIBUSB_SPEED_UNKNOWN, "UNKNOWN"},
        {LIBUSB_SPEED_LOW,     "LOW    "},
        {LIBUSB_SPEED_FULL,    "FULL   "},
        {LIBUSB_SPEED_HIGH,    "HIGH   "},
        {LIBUSB_SPEED_SUPER,   "SUPER  "},
    };

    return value2text( value, v2t, sizeof( v2t ) / sizeof( v2t[0] ) );
}


const char* descriptor_type_to_text( int value )
{
    static value2text_t v2t[] =
    {
        {LIBUSB_DT_DEVICE,    "DEVICE"},
        {LIBUSB_DT_CONFIG,    "CONFIG"},
        {LIBUSB_DT_STRING,    "STRING"},
        {LIBUSB_DT_INTERFACE, "INTERFACE"},
        {LIBUSB_DT_ENDPOINT,  "ENDPOINT"},
        {LIBUSB_DT_HID,       "HID"},
        {LIBUSB_DT_REPORT,    "REPORT"},
        {LIBUSB_DT_PHYSICAL,  "PHYSICAL"},
        {LIBUSB_DT_HUB,       "HUB"},
    };

    return value2text( value, v2t, sizeof( v2t ) / sizeof( v2t[0] ) );
}


const char* class_to_text( int value )
{
    static value2text_t v2t[] =
    {
        {LIBUSB_CLASS_PER_INTERFACE,       "PER_INTERFACE"},
        {LIBUSB_CLASS_AUDIO,               "AUDIO"},
        {LIBUSB_CLASS_COMM,                "COMM"},
        {LIBUSB_CLASS_HID,                 "HID"},
        {LIBUSB_CLASS_PHYSICAL,            "PHYSICAL"},
        {LIBUSB_CLASS_PRINTER,             "PRINTER"},
        {LIBUSB_CLASS_IMAGE,               "IMAGE"},
        {LIBUSB_CLASS_MASS_STORAGE,        "MASS_STORAGE"},
        {LIBUSB_CLASS_HUB,                 "HUB"},
        {LIBUSB_CLASS_DATA,                "DATA"},
        {LIBUSB_CLASS_SMART_CARD,          "SMART_CARD"},
        {LIBUSB_CLASS_CONTENT_SECURITY,    "CONTENT_SECURITY"},
        {LIBUSB_CLASS_VIDEO,               "VIDEO"},
        {LIBUSB_CLASS_PERSONAL_HEALTHCARE, "PERSONAL_HEALTHCARE"},
        {LIBUSB_CLASS_DIAGNOSTIC_DEVICE,   "DIAGNOSTIC_DEVICE"},
        {LIBUSB_CLASS_WIRELESS,            "WIRELESS"},
        {LIBUSB_CLASS_APPLICATION,         "APPLICATION"},
        {LIBUSB_CLASS_VENDOR_SPEC,         "VENDOR_SPEC"},
    };

    return value2text( value, v2t, sizeof( v2t ) / sizeof( v2t[0] ) );
}


const char* endpoint_direction_to_text( int value )
{
    static value2text_t v2t[] =
    {
        {LIBUSB_ENDPOINT_IN,  "IN"},
        {LIBUSB_ENDPOINT_OUT, "OUT"},
    };

    return value2text( value, v2t, sizeof( v2t ) / sizeof( v2t[0] ) );
}


const char* transfer_type_to_text( int value )
{
    static value2text_t v2t[] =
    {
        {LIBUSB_TRANSFER_TYPE_CONTROL,     "CONTROL"},
        {LIBUSB_TRANSFER_TYPE_ISOCHRONOUS, "ISOCHRONOUS"},
        {LIBUSB_TRANSFER_TYPE_BULK,        "BULK"},
        {LIBUSB_TRANSFER_TYPE_INTERRUPT,   "INTERRUPT"},
        {LIBUSB_TRANSFER_TYPE_BULK_STREAM, "BULK_STREAM"},
    };

    return value2text( value, v2t, sizeof( v2t ) / sizeof( v2t[0] ) );
}


const char* synchronization_type_to_text( int value )
{
    static value2text_t v2t[] =
    {
        {LIBUSB_ISO_SYNC_TYPE_NONE,     ""},
        {LIBUSB_ISO_SYNC_TYPE_ASYNC,    "ASYNC"},
        {LIBUSB_ISO_SYNC_TYPE_ADAPTIVE, "ADAPTIVE"},
        {LIBUSB_ISO_SYNC_TYPE_SYNC,     "SYNC"},
    };

    return value2text( value, v2t, sizeof( v2t ) / sizeof( v2t[0] ) );
}


const char* isochronous_to_text( int value )
{
    static value2text_t v2t[] =
    {
        {LIBUSB_ISO_USAGE_TYPE_DATA,     "DATA"},
        {LIBUSB_ISO_USAGE_TYPE_FEEDBACK, "FEEDBACK"},
        {LIBUSB_ISO_USAGE_TYPE_IMPLICIT, "IMPLICIT"},
    };

    return value2text( value, v2t, sizeof( v2t ) / sizeof( v2t[0] ) );
}


static void print_device_desc( libusb_device* dev )
{
    struct libusb_device_descriptor desc;

    int r = libusb_get_device_descriptor( dev, &desc );
    if ( r < 0 ) {
        fprintf( stderr, "Error: failed to get device descriptor" );
        return;
    }

    printf( "Device descriptor\n" );
    printf( "-----------------\n" );
    printf( "  Size of the descriptor             : %d\n",          desc.bLength );
    printf( "  Descriptor type                    : 0x%02X   %s\n", desc.bDescriptorType, descriptor_type_to_text( desc.bDescriptorType ) );
    printf( "  USB specification                  : 0x%04X\n",      desc.bcdUSB );
    printf( "  USB-IF class code                  : 0x%02X   %s\n", desc.bDeviceClass, class_to_text( desc.bDeviceClass ) );
    printf( "  USB-IF subclass code               : 0x%02X\n",      desc.bDeviceSubClass );
    printf( "  USB-IF protocol code               : 0x%02X\n",      desc.bDeviceProtocol );
    printf( "  Maximum packet size for endpoint 0 : %d\n",          desc.bDeviceProtocol );
    printf( "  USB-IF vendor ID                   : 0x%04X\n",      desc.idVendor );
    printf( "  USB-IF product ID                  : 0x%04X\n",      desc.idProduct );
    printf( "  Device release number              : 0x%04X\n",      desc.bcdDevice );
    printf( "  Index of manufacturer string       : 0x%02X\n",      desc.iManufacturer );
    printf( "  Index of product string            : 0x%02X\n",      desc.iProduct );
    printf( "  Index of serial number string      : 0x%02X\n",      desc.iSerialNumber );
    printf( "  Number of possible configurations  : 0x%02X\n",      desc.bNumConfigurations );
    printf( "\n" );
}


static void print_device_connection( libusb_device* dev )
{
    int     i, real_port_depth;
    uint8_t port_numbers[MAX_PORT_NUMBERS];
    libusb_device_handle* handle;
    int     config;
    int     r;

    printf( "  Bus number                         : 0x%02X\n", libusb_get_bus_number( dev ) );
    printf( "  Port number                        : 0x%02X\n", libusb_get_port_number( dev ) );
    real_port_depth = libusb_get_port_numbers( dev, port_numbers, MAX_PORT_NUMBERS );
    if ( ( real_port_depth > 0 ) && ( real_port_depth != LIBUSB_ERROR_OVERFLOW ) ) {
        printf( "  Port path from root                : " );
        for ( i = 0; i < real_port_depth; i++ ) {
            printf( "0x%02X", port_numbers[i] );
            if ( i != real_port_depth - 1 ) {
                printf( ", " );
            }
        }
        printf( "\n" );
    }
    printf( "  Device address                     : 0x%02X\n", libusb_get_device_address( dev ) );
    printf( "  Device speed                       : 0x%02X   %s\n", libusb_get_device_speed( dev ), speed_to_text( libusb_get_device_speed( dev ) ) );

    r = libusb_open( dev, &handle );
    if ( r == 0 ) {
        libusb_get_configuration( handle, &config );
        printf( "  Currently active configuration     : %d\n", config );
        libusb_close( handle );
    }

    printf( "\n" );
}


static void print_endpoint( const struct libusb_endpoint_descriptor *endp )
{
    printf( "      Endpoint descriptor\n" );
    printf( "      -------------------\n" );

    printf( "      Size of this descriptor               : %d\n",          endp->bLength );
    printf( "      Descriptor type                       : 0x%02X   %s\n", endp->bDescriptorType, descriptor_type_to_text( endp->bDescriptorType ) );
    printf( "      Endpoint address                      : 0x%02X   %s\n", endp->bEndpointAddress & 0x0F, endpoint_direction_to_text( endp->bEndpointAddress & 0x80 ) );
    printf( "      Attributes                            : 0x%02X   %s %s %s\n",
            endp->bmAttributes,
            transfer_type_to_text( endp->bmAttributes & 0x03 ),
            synchronization_type_to_text( ( endp->bmAttributes & 0x0C ) >> 2 ),
            isochronous_to_text( ( endp->bmAttributes & 0x30 ) >> 4 ) );
    printf( "      Maximum packet size for the endpoint  : %d\n",          endp->wMaxPacketSize );
    printf( "      Interval for polling endpoint         : %d\n",          endp->bInterval );
    printf( "      Audio devices only: rate of feedback  : %d\n",          endp->bRefresh );
    printf( "      Audio devices only: address of synch  : 0x%02X\n",      endp->bSynchAddress );

    printf( "\n" );
}


static void print_interface( const struct libusb_interface *interface )
{
    int i, j;

    printf( "\n" );
    printf( "  Interface\n" );
    printf( "  =========\n" );
    printf( "\n" );

    for ( i = 0; i < interface->num_altsetting; i++ ) {
        const struct libusb_interface_descriptor* idesc = &interface->altsetting[i];

        printf( "    Alt-Interface descriptor\n" );
        printf( "    ------------------------\n" );

        printf( "    Size of this descriptor               : %d\n",          idesc->bLength );
        printf( "    Descriptor type                       : 0x%02X   %s\n", idesc->bDescriptorType, descriptor_type_to_text( idesc->bDescriptorType ) );
        printf( "    Number of this interface              : %d\n",          idesc->bInterfaceNumber );
        printf( "    Value used for this alternate setting : %d\n",          idesc->bAlternateSetting );
        printf( "    Number of endpoints                   : %d\n",          idesc->bNumEndpoints );
        printf( "    USB-IF class code                     : 0x%02X   %s\n", idesc->bInterfaceClass, class_to_text( idesc->bInterfaceClass ) );
        printf( "    USB-IF subclass code                  : 0x%02X\n",      idesc->bInterfaceSubClass );
        printf( "    USB-IF protocol code                  : 0x%02X\n",      idesc->bInterfaceProtocol );
        printf( "    Index of string descriptor            : 0x%02X\n",      idesc->iInterface );
        printf( "\n" );

        for ( j = 0; j < idesc->bNumEndpoints; j++ ) {
            const struct libusb_endpoint_descriptor* endp = &idesc->endpoint[j];
            print_endpoint( endp );
        }
    }
}


static void print_active_config( libusb_device* dev )
{
    struct libusb_config_descriptor *config;
    int i;  

    int r = libusb_get_active_config_descriptor( dev, &config );
    if ( r != 0 ) {
        return;
    }

    printf( "  Active configuration\n" );
    printf( "  --------------------\n" );

    printf( "  Size of this descriptor            : %d\n",          config->bLength );
    printf( "  Descriptor type                    : 0x%02X   %s\n", config->bDescriptorType, descriptor_type_to_text( config->bDescriptorType ) );
    printf( "  Total length of data               : %d\n",          config->wTotalLength );
    printf( "  Number of interfaces               : %d\n",          config->bNumInterfaces );
    printf( "  Identifier value                   : 0x%02X\n",      config->bConfigurationValue );
    printf( "  Index of string descriptor         : 0x%02X\n",      config->iConfiguration );
    printf( "  Configuration characteristics      : 0x%02X\n",      config->bmAttributes );
    printf( "  Maximum power consumption          : 0x%02X\n",      config->MaxPower );

    for ( i = 0; i < config->bNumInterfaces; i++ ) {
        const struct libusb_interface* interface = &config->interface[i];
        print_interface( interface );
    }

    printf( "\n" );
}


static void print_devs( libusb_device **devs )
{
    libusb_device *dev;
    int i = 0;

    while ( ( dev = devs[i++] ) != NULL ) {
        printf( "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n" );
        print_device_desc( dev );
        print_device_connection( dev );
        print_active_config( dev );
        printf( "\n" );
    }
}


int main( void )
{
    libusb_device **devs;
    int r;
    ssize_t cnt;

    r = libusb_init( NULL );
    if ( r < 0 )
        return r;

    cnt = libusb_get_device_list( NULL, &devs );
    if ( cnt < 0 )
        return (int)cnt;

    print_devs( devs );
    libusb_free_device_list( devs, 1 );

    libusb_exit( NULL );
    return 0;
}
