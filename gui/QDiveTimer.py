from PyQt5.QtCore import QObject, QTime, QTimer


class QDiveTimer(QObject):
    def __init__(self, parent=None) -> None:
        QObject.__init__(self, parent)

        self.__time = QTime(0, 0, 0)
        self.__paused = False
        self.__started = False

        self.__timer = QTimer()
        self.__timer.timeout.connect(self.__update)

    def start(self) -> None:
        """Start the dive timer.
        """

        if not self.__paused and self.__started:
            return

        self.__paused = False
        self.__started = True

        self.__timer.start(1000)

    def pause(self) -> None:
        """Pause the dive timer.
        """

        if self.__paused:
            return

        self.__paused = True

        self.__timer.stop()

    def stop(self) -> None:
        """Stop the dive timer.
        """

        self.__timer.stop()

        self.__paused = False
        self.__started = False
        self.__time = QTime(0, 0, 0)

    @property
    def elapsed(self) -> int:
        """Helper property.

        Returns
        -------
        int
            the time elapsed in seconds
        """

        return self.__time.hour() * 3600 + self.__time.minute() * 60 + self.__time.second()

    @property
    def started(self) -> bool:
        """Check whether the dive timer has started or not.

        Returns
        -------
        bool
            True, if the timer has started, False otherwise
        """

        return self.__started

    @property
    def paused(self) -> bool:
        """Check whether the dive timer has paused or not.

        Returns
        -------
        bool
            True, if the timer has paused, False otherwise
        """

        return self.__paused

    @property
    def time(self) -> str:
        """Get the diving time.

        Returns
        -------
        str
            diving time in format hh:mm:ss
        """

        return self.__time.toString('hh:mm:ss')

    def __update(self):
        self.__time = self.__time.addSecs(1)
