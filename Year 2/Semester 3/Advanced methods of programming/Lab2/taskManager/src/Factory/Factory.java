package Factory;

import Container.ContainterInterface;
import Enum.ContainerStrategy;

public interface Factory {
    ContainterInterface createContainer(ContainerStrategy strategy);
}
